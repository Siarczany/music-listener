#include "listitem.h"

#include "listview.h"

class ListView;

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
