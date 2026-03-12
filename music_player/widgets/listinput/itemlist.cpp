#include "itemlist.h"

#include "listitem.h"

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
                emit deleted();
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

void ItemList::setLabel(const QString &text)
{
    labelText = text;
}

QStringList ItemList::getList() const
{
    QStringList returning;
    for(auto element : model->getAll())
    {
        ItemData* data = static_cast<ItemData*>(element);
        returning.append(data->name);
    }
    return returning;
}

void ItemList::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    emit hiddenWidget->sizeChanged();
}

void ItemList::refresh()
{
    view->refresh(model->getAll());

    QString text = labelText;
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
