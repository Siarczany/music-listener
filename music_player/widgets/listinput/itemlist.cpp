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

    // random ass width
    // maybe make it resizable in the future
    setFixedWidth(133);

    refresh();

    // hidding the widget
    connect(hiddenWidget, &HiddenWidget::inSight,
            this, ItemList::inSight);

    connect(view, &ListView::deleted,
            this, [this](int index){
                model->remove(index);
                refresh();
                emit deleted();
            });

    // ListView can be resized so resize this as well
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
    if(model->count() > 1) // >= 2
        return;

    // add or update the first element
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
    // first element is added via addFirst so set flag and get out
    if(firstLockedIn == false)
    {
        firstLockedIn = true;
        return;
    }

    // just add new element
    ItemData* data = new ItemData();
    data->name = text;
    model->add(data);
    refresh();
}

void ItemList::setLabelText(const QString &text)
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
    emit sizeChanged();
}

void ItemList::inSight(bool visibility)
{
    if(visibility == false)
    {
        hwd.width = width();
        setFixedWidth(10);
    }
    else // visibility == true
    {
        setFixedWidth(hwd.width);
    }
    setVisible(visibility);
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
