#pragma once

#include <QWidget>
#include <QListWidget>
#include "model.h"
#include "item.h"
#include "itemwidgetbase.h"
#include <QVBoxLayout>
#include "mylistwidget.h"

// base class for view/list
// view comes from mvvm(movel view viewmodel) so I am using it xd
class ViewBase : public QWidget
{
    Q_OBJECT
public:
    // because templates don't work with Q_OBJECT we just hold an instance of an
    //  item and this item creates other items xd
    ViewBase(ItemWidgetBase* factory, QWidget* parent = nullptr);
    ~ViewBase();

    // refreshes the view using data from a model
    void refresh(const QVector<ModelData*>& data);

    // sets current row and manages previous row
    void setCurrentRow(const int row);
signals:
    void currentRowChanged(int row);
private:
    // actually idk why this class doesn't dziedziczyć z MyListWidget
    MyListWidget* m_listWidget = nullptr;

    // factory because templates and Q_OBJECT
    Item<ItemWidgetBase>* factory = nullptr;

    // layout for list
    QVBoxLayout* layout;

    int previousRow = -1;
    int currentRow = -1;

    // creates new item via factory and adds it
    void addItem(ModelData* data, const int index);

    // QListWidget is stupid so we need our own function to fight QListWidget
    void selectPressedItem(QListWidgetItem* item);

    // sets specific item as fully visible or not
    void setItemFullyVisible(const bool visibility, const int row);

    // for getting widgets or items for updating widgets contents and what not
    ItemWidgetBase* getWidgetForRow(int row);
    ItemWidgetBase* getWidgetForItem(QListWidgetItem* item);
    Item<ItemWidgetBase>* getItemForRow(int row);
};

