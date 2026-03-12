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

    connect(m_listWidget, &MyListWidget::itemEntered,
            this, &ViewBase::selectPressedItem);
    connect(m_listWidget, &MyListWidget::itemPressed,
            this, &ViewBase::selectPressedItem);

    connect(this, &ViewBase::currentRowChanged,
            this, [this](int current){
        //qDebug() << current;
        if(current >= 0)
        {
            ItemWidgetBase* widget = getWidgetForRow(current);
            if(widget)
                widget->setFullyVisible(true);
            Item<ItemWidgetBase>* item = getItemForRow(current);
            if(item)
                item->updateSizeHint();
        }
        if(previousRow >= 0)
        {
            ItemWidgetBase* widget = getWidgetForRow(previousRow);
            if(widget)
                widget->setFullyVisible(false);
            Item<ItemWidgetBase>* item = getItemForRow(previousRow);
            if(item)
                item->updateSizeHint();
        }
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
        //qDebug() << i;
        if(i < dataCount && i < listCount)
        {
            ItemWidgetBase* widget = getWidgetForRow(i);
            if(!widget)
                continue;
            widget->update(data[i]);
            //qDebug() << "update";
        }

        if(i >= dataCount)
        {
            delete m_listWidget->takeItem(i);
            //qDebug() << "dlete";
            deletedAny = true;
        }

        if(i >= listCount)
        {
            addItem(data[i], i);
            //qDebug() << "adding";
        }
    }
    if(deletedAny){
        //setCurrentRow(-1);
        //qDebug() << "deleted so setting at -1";
        setCurrentRow(-1);
    }
}

void ViewBase::setCurrentRow(const int row)
{
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

    widget->connectToList(this, index);
}

void ViewBase::selectPressedItem(QListWidgetItem *item)
{
    if(m_listWidget->isMousePressed() == false)
        return;
    m_listWidget->setCurrentItem(item);
    setCurrentRow(m_listWidget->currentRow());
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


