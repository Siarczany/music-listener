#pragma once

#include <QWidget>
#include "modeldata.h"

// class definition of ViewBase needed for ItemWidgetBase by the compiler
class ViewBase;

// base class for the item that will sit in the list inside view
class ItemWidgetBase : public QWidget
{
    Q_OBJECT
public:
    ItemWidgetBase(QWidget* parent)
        : QWidget(parent)
    {}
    virtual ~ItemWidgetBase() = default;

    // when we click an item inside a list it can display something
    //  for exmaple a delete button
    virtual void setFullyVisible(bool visible) = 0;

    // updates the data inside this item
    //  deleting all the items and creating them again is expensive I think
    //  and if I remember correctly you can see visible flickering  when that
    //  happenes
    // also I planned to make a lazy loaded vieww at first so this wwould also be
    //  for it xd
    virtual void update(ModelData* data) = 0;

    // for signals to travel from an item to a list
    virtual void connectToList(ViewBase* list, int index) = 0;

    // factory function because qt doesn't like templates and Q_OBJECTs together
    // creates a new item of itself
    virtual ItemWidgetBase* nowy(QWidget* parent, ModelData* data = nullptr) = 0;
};
