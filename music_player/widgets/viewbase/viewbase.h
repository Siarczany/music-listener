#pragma once

#include <QWidget>
#include <QListWidget>
#include "model.h"
#include "item.h"
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
    void setCurrentRow(const int row);
signals:
    void currentRowChanged(int row);
private:
    MyListWidget* m_listWidget = nullptr;
    Item<ItemWidgetBase>* factory = nullptr;
    QVBoxLayout* layout;

    int previousRow = -1;
    int currentRow = -1;

    void addItem(ModelData* data, const int index);
    void selectPressedItem(QListWidgetItem* item);

    ItemWidgetBase* getWidgetForRow(int row);
    ItemWidgetBase* getWidgetForItem(QListWidgetItem* item);
    Item<ItemWidgetBase>* getItemForRow(int row);
};

