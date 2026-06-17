#include "viewbase.h"

ViewBase::ViewBase(ItemWidgetBase *factory, QWidget *parent)
    : QWidget(parent)
    , m_listWidget(new MyListWidget(this))
    , layout(new QVBoxLayout(this))
{
    this->factory = new Item<ItemWidgetBase>(nullptr, factory);

    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_listWidget);

    // edge case when user holds the mouse key and moves the mouse to some other
    //  item would move the focus(?) to this new item but the old widget would
    //  lose its focus(?) and this blue thing on top that says it is selected
    //  and the new item wouldn't call setFullyVisible(true)
    connect(m_listWidget, &MyListWidget::itemEntered,
            this, &ViewBase::selectPressedItem);

    connect(m_listWidget, &MyListWidget::itemPressed,
            this, &ViewBase::selectPressedItem);

    connect(this, &ViewBase::currentRowChanged,
            this, [this](int current){
        //qDebug() << current;
        setItemFullyVisible(true, current);
        setItemFullyVisible(false, previousRow);
    });
}

ViewBase::~ViewBase()
{
    delete factory;
}

void ViewBase::refresh(const QVector<ModelData *> &data)
{
    int max = std::max(m_listWidget->count(),
                       (int)data.size());
    bool deletedAny = false;
    int dataCount = data.size();
    int listCount = m_listWidget->count();

    for(int i = 0; i<max; i++)
    {
        // just update the inside
        if(i < dataCount && i < listCount)
        {
            ItemWidgetBase* widget = getWidgetForRow(i);
            if(!widget)
                continue;
            widget->update(data[i]);
        }

        // delete the extra item
        if(i >= dataCount)
        {
            delete m_listWidget->takeItem(i);
            deletedAny = true;
        }

        // add missing one
        if(i >= listCount)
        {
            addItem(data[i], i);
        }
    }

    // I am assuming that the currently selected item can be deleted because I
    //  don't want to have X buttons in every item visible at once
    //  so that means we deleted what was highlighted and how nothing should be
    //  highlighted so row = -1
    // idk but I think setting row to -1 tells QListWidget to not select anything
    if(deletedAny){
        setCurrentRow(-1);
    }
}

void ViewBase::setCurrentRow(const int row)
{
    // don't set current = previous
    if(row == currentRow)
        return;

    m_listWidget->setCurrentRow(row);

    previousRow = currentRow;
    currentRow = row;

    emit currentRowChanged(currentRow);
}

void ViewBase::addItem(ModelData *data, const int index)
{
    Item<ItemWidgetBase>* item =
        factory->nowy(m_listWidget);
    item->setTrueRow(index);
    ItemWidgetBase* widget = item->getWidget();
    widget->update(data);

    // connect list slots with widget signals via widget because we don't
    //  know what siganls there are
    // because we update the widget insides and not create a new ones when one
    //  deleted indexes stay correct even after deletions
    //  but if this moves to a lazy loaded list than indexes would somehow need
    //  to be updated :(
    widget->connectToList(this, index);
}

void ViewBase::selectPressedItem(QListWidgetItem *item)
{
    if(m_listWidget->isMousePressed() == false)
        return;
    m_listWidget->setCurrentItem(item);
    setCurrentRow(m_listWidget->currentRow());
}

void ViewBase::setItemFullyVisible(const bool visibility, const int row)
{
    if(row >= 0)
    {
        ItemWidgetBase* widget = getWidgetForRow(row);
        if(widget)
            widget->setFullyVisible(visibility);
        Item<ItemWidgetBase>* item = getItemForRow(row);
        if(item)
            item->updateSizeHint();
    }
}

ItemWidgetBase *ViewBase::getWidgetForRow(int row)
{
    QListWidgetItem* item = m_listWidget->item(row);
    return getWidgetForItem(item);
}

ItemWidgetBase *ViewBase::getWidgetForItem(QListWidgetItem *item)
{
    if(item == nullptr)
        return nullptr;
    Item<ItemWidgetBase>* itemWidget =  static_cast<Item<ItemWidgetBase>*>(item);
    return itemWidget->getWidget();
}

Item<ItemWidgetBase> *ViewBase::getItemForRow(int row)
{
    return static_cast<Item<ItemWidgetBase>*>(m_listWidget->item(row));
}


