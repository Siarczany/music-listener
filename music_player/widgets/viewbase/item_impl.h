# pragma once

#include "item.h"
template<typename T>
Item<T>::Item(QListWidget* parent, T* widget)
    : QListWidgetItem(parent)
    , widget(widget)
{}

template<typename T>
Item<T>::~Item()
{
    // widget is created by the view and view is it's parent so nothing to
    //  delete here
}

template<typename T>
void Item<T>::setTrueRow(const int row)
{
    trueRow = row;
}

template<typename T>
void Item<T>::updateSizeHint()
{
    setSizeHint(widget->sizeHint());
}

template<typename T>
T* Item<T>::getWidget() const
{
    return widget;
}

template<typename T>
void Item<T>::setWidget(T *widget)
{
    this->widget = widget;
}

template<typename T>
Item<T>* Item<T>::nowy(QListWidget *parent)
{
    auto* item = new Item<T>(parent, nullptr);
    T* widget = this->widget->nowy(parent);
    item->setWidget(widget);

    addToParent(parent, item, widget);
    return item;
}

template<typename T>
void Item<T>::addToParent(QListWidget *parent, Item<T> *item, T *widget)
{
    parent->setItemWidget(item, widget);
    //item->updateSizeHint();
    widget->setFullyVisible(false);
}



