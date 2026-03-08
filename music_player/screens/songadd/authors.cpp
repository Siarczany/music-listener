#include "authors.h"

AuthorsList::AuthorsList(QWidget *parent)
    : QWidget(parent)
    , layout(new QVBoxLayout(this))
    , hiddenWidget(new HiddenWidget(this, this))
    , model(new Model())
    , view(new AuthorsView(new AuthorItem()))
{
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(view);

    refresh();

    connect(hiddenWidget, &HiddenWidget::inSight,
            this, [this](bool visibility){
        setVisible(visibility);
    });

    connect(view, &AuthorsView::deleted,
            this, [this](int index){
        model->remove(index);
        //view->refresh(model->getAll());
        refresh();
    });

    connect(view, &AuthorsView::sizeChanged,
            this, [this](){
        setFixedWidth(view->width());
        emit sizeChanged();
    });


    emit hiddenWidget->inSight(false);
}

AuthorsList::~AuthorsList()
{
    delete model;
}

HiddenWidget *AuthorsList::getHiddenWidget() const
{
    return hiddenWidget;
}

int AuthorsList::count() const
{
    return model->count();
}


void AuthorsList::addFirst(const QString &text)
{
    if(model->count() > 1)
        return;
    if(model->count() == 0 && firstLockedIn == false)
    {
        Author* author = new Author();
        author->name = text;
        model->add(author);
        //view->refresh(model->getAll());
        refresh();
    }
    if(model->count() == 1 && firstLockedIn == false)
    {
        Author* author = new Author();
        author->name = text;
        model->update(0, author);
        //view->refresh(model->getAll());
        refresh();
    }
}

void AuthorsList::add(const QString &text)
{
    if(firstLockedIn == false)
    {
        firstLockedIn = true;
        return;
        // gdy wybieramy text z popupa najpierw jest on setowany na tekst
        // co wytwwarza sygnał że tekst się zmienił
        // co z kolei zmienia tekst 1. autora przez co jest on już poprawwny
        // i nie musimy go settoawć jeszcze raz :)
    }
    Author* author = new Author();
    author->name = text;
    model->add(author);
    //view->refresh(model->getAll());
    refresh();
}

void AuthorsList::resizeEvent(QResizeEvent *event)
{
    qDebug() << "resize!";
    emit hiddenWidget->sizeChanged();
}

void AuthorsList::refresh()
{
    view->refresh(model->getAll());;
    QString text = "Autorzy";
    QString bracket1 = "(";
    QString bracket2 = ")";

    if(model->count() != 0)
    {
        text  = text
               + bracket1
               + QString::fromStdString(std::to_string(model->count()))
               + bracket2;
    }

    emit hiddenWidget->setLabel(text);


    //hiddenWidget->setLabel("Autorzy(" +);
}

AuthorItem::AuthorItem(QWidget *parent, ModelData *data)
    : ItemWidgetBase(parent)
    , layout(new QHBoxLayout(this))
    , text(new QLabel("bombardino krokodilo"))
    , del(new QPushButton("x"))
{
    layout->setContentsMargins(0, 0, 0, 0);
    del->setFixedSize(24, 24);

    layout->addWidget(text);
    layout->addStretch();
    layout->addWidget(del);

    update(data);

    setFullyVisible(false);

    connect(del, &QPushButton::clicked,
            this, &AuthorItem::deleted);
}

AuthorItem::~AuthorItem()
{

}

void AuthorItem::setFullyVisible(bool visible)
{
    del->setVisible(visible);
}

void AuthorItem::update(ModelData *data)
{
    if(data == nullptr)
        return;
    Author* newData = static_cast<Author*>(data);
    text->setText(newData->name);
}

void AuthorItem::connectToList(ViewBase *list, int index)
{
    AuthorsView* view = static_cast<AuthorsView*>(list);
    connect(this, &AuthorItem::deleted,
            this, [view, index](){
        emit view->deleted(index);
    });
}

ItemWidgetBase *AuthorItem::nowy(QWidget *parent, ModelData *data)
{
    AuthorItem* item = new AuthorItem(parent, data);
    return item;
}

AuthorsView::AuthorsView(ItemWidgetBase *factory, QWidget *parent)
    : ViewBase(factory, parent)
{
    resizableWidget = new ResizableWidget(this, this);
    connect(resizableWidget, &ResizableWidget::sizeChanged,
            this, [this](){
        emit sizeChanged();
    });
}

void AuthorsView::resizeEvent(QResizeEvent *event)
{
    ViewBase::resizeEvent(event);
    resizableWidget->resize();
}
