#pragma once

#include <QWidget>
#include "model.h"
#include <QListWidgetItem>

// intermediatory(idk how to spell) class between an item in a list(QWidget) and
//  a QListWidget
// for some ungodly reason qt allows to have a pointer to a class containing
//  Q_OBJECT inside a template class but doesn't like them together in one class
//  xd
// maybe it is possible to create a virtual/skip this class but I've done it like
//  this and it works xd
// also at first I wanted to make a lazy loaded list so this class also holds the
//  true index of an item
// T is for an item widget
template<typename T>
class Item : public QListWidgetItem
{
public:
    Item<T>(QListWidget *parent, T* widget);

    ~Item();

    // there were plans to do a lazy loaded list so here is something I would need
    //  I think
    void setTrueRow(const int row);

    // the same as above, this doesn't even have an implementation xd
    int getTrueRow() const;

    // sets size hint for this Item
    //  qt is qt and there is an actual widget in the list QListWidget
    //  and there is QListWidgetItem this is this class which holds the actual
    //   widget
    void updateSizeHint();

    // since this isn't the actual widget we need a way to get it
    T* getWidget() const;

    // -||- set it
    void setWidget(T* widget);

    // factory because as in ItemWidgetBase qt doesn;t like templates and
    //  Q_OBJECTs
    // also we add the item to the list in this function
    Item<T>* nowy(QListWidget* parent);
private:

    void addToParent(QListWidget* parent, Item<T>* item, T* widget);

    // not used currently
    int trueRow;

    T* widget;
};

#include "item_impl.h"
