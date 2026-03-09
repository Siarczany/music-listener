#include "listinput.h"



ListItem::ListItem(QWidget *parent, ModelData *data)
    : ItemWidgetBase(parent)
    , layout(new QHBoxLayout(this))
    , label(new QLabel("droprate trollujący"))
    , del(new QPushButton("x"))
{
    layout->setContentsMargins(0, 0, 0, 0);
    del->setFixedSize(24, 24);

    layout->addWidget(label);
    layout->addStretch();
    layout->addWidget(del);

    update(data);

    setFullyVisible(false);

    connect(del, &QPushButton::clicked,
            this, &ListItem::deleted);
}

ListItem::~ListItem()
{

}

void ListItem::setFullyVisible(bool visible)
{
    del->setVisible(visible);
}

void ListItem::update(ModelData *data)
{
    if(data == nullptr)
        return;
    ItemData* newData = static_cast<ItemData*>(data);
    label->setText(newData->name);
}

void ListItem::connectToList(ViewBase *list, int index)
{
    ListView* view = static_cast<ListView*>(list);
    connect(this, &ListItem::deleted,
            this, [view, index](){
        emit view->deleted(index);
    });
}

ItemWidgetBase *ListItem::nowy(QWidget *parent, ModelData *data)
{
    ListItem* item = new ListItem(parent, data);
    return item;
}



ListView::ListView(ItemWidgetBase *factory, QWidget *parent)
    : ViewBase(factory, parent)
{
    resizableWidget = new ResizableWidget(this, this);
    connect(resizableWidget, &ResizableWidget::sizeChanged,
            this, [this](){
        emit sizeChanged();
    });
}

void ListView::resizeEvent(QResizeEvent *event)
{
    ViewBase::resizeEvent(event);
    resizableWidget->resize();
}








ItemList::ItemList(QWidget *parent)
    : QWidget(parent)
    , layout(new QVBoxLayout(this))
    , hiddenWidget(new HiddenWidget(this, this))
    , model(new Model())
    , view(new ListView(new ListItem()))
{
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(view);

    setFixedWidth(133);

    refresh();

    connect(hiddenWidget, &HiddenWidget::inSight,
            this, [this](bool visibility){
        setVisible(visibility);
    });

    connect(view, &ListView::deleted,
            this, [this](int index){
        model->remove(index);
        refresh();
    });

    connect(view, &ListView::sizeChanged,
            this, [this](){
        setFixedWidth(view->width());
        emit sizeChanged();
    });
}

ItemList::~ItemList()
{
    delete model;
}

HiddenWidget *ItemList::getHiddenWidget() const
{
    return hiddenWidget;
}

int ItemList::count() const
{
    return model->count();
}

void ItemList::addFirst(const QString &text)
{
    if(model->count() > 1)
        return;
    if(model->count() == 0 && firstLockedIn == false)
    {
        ItemData* data = new ItemData();
        data->name = text;
        model->add(data);
        refresh();
    }
    if(model->count() == 1 && firstLockedIn == false)
    {
        ItemData* data = new ItemData();
        data->name = text;
        model->update(0, data);
        refresh();
    }
}

void ItemList::add(const QString &text)
{
    if(firstLockedIn == false)
    {
        firstLockedIn = true;
        return;
    }
    ItemData* data = new ItemData();
    data->name = text;
    model->add(data);
    refresh();
}

void ItemList::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    emit hiddenWidget->sizeChanged();
}

void ItemList::refresh()
{
    view->refresh(model->getAll());

    QString text = "Spoofs";
    QString bracket1 = "(";
    QString bracket2 = ")";

    if(model->count() != 0)
    {
        text = text
               + bracket1
               + QString::fromStdString(std::to_string(model->count()))
               + bracket2;
    }

    emit hiddenWidget->setLabel(text);
}



ListInput::ListInput(QWidget *parent)
    : QWidget(parent)
    , layout(new QVBoxLayout(this))
    , input(new NiceLineEdit(this, NiceLineEdit::LineEdit::Suggestion))
    , list(new ItemList(this))
{
    hideable = new HideableWidget(list, list->getHiddenWidget(), this);
    suggestionInput = static_cast<SuggestionLineEdit*>(input->getLineEdit());
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    input->setLabel("dsaasd");
    hideable->setText("asddsa");

    suggestionInput->setQuery([this](const QString& text){
        QStringList all;
        all << "asd" << "sdf" << "dfg" << "fgh" << "ghj" << "hjk" << "jkl";

        QStringList ret;

        for(QString& str : all)
        {
            if(rand()%3 == 0)
            {
                ret << str;
            }
        }
        return ret;
    });

    layout->addWidget(input, 0, Qt::AlignHCenter);
    layout->addWidget(hideable, 0, Qt::AlignHCenter);

    connect(suggestionInput, &SuggestionLineEdit::textChanged,
            this, [this](){
        list->addFirst(suggestionInput->text());
    });
    connect(suggestionInput, &SuggestionLineEdit::choosen,
            this, [this](){
        list->add(suggestionInput->text());
        suggestionInput->clear();
    });
    connect(suggestionInput, &SuggestionLineEdit::returnPressed,
            this, [this](){
        list->add(suggestionInput->text());
        suggestionInput->clear();
    });
}

ListInput::~ListInput()
{

}
