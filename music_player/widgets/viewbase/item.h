#pragma once

#include <QWidget>
#include "model.h"
#include <QListWidgetItem>

class ViewBase;

class ItemWidgetBase : public QWidget
{
    Q_OBJECT
public:
    ItemWidgetBase(QWidget* parent)
        : QWidget(parent)
    {}
    virtual ~ItemWidgetBase() = default;

    virtual void setFullyVisible(bool visible) = 0;

    virtual void update(ModelData* data) = 0;

    virtual void connectToList(ViewBase* list, int index) = 0;

    virtual ItemWidgetBase* nowy(QWidget* parent, ModelData* data = nullptr) = 0;
};

template<typename T>
class Item : public QListWidgetItem
{
public:
    Item(QListWidget *parent)
        : QListWidgetItem(parent)
        , widget(new T(nullptr))
    {
        addToParent(parent, this, widget);
    }
    Item<T>(QListWidget *parent, T* widget)
        : QListWidgetItem(parent)
        , widget(widget)
    {}

    ~Item(){
        //delete widget;
    }

    void setTrueRow(const int row){trueRow = row;}
    int getTrueRow() const{return trueRow;}

    void updateSizeHint()
    {
        setSizeHint(widget->sizeHint());
    }

    T* getWidget() const{return widget;}
    void setWidget(T* widget){
        this->widget = widget;
    }

    Item<T>* nowy(QListWidget* parent){
        auto* item = new Item<T>(parent, nullptr);
        T* widget = this->widget->nowy(parent);
        item->setWidget(widget);

        addToParent(parent, item, widget);
        return item;
    }
private:
    void addToParent(QListWidget* parent, Item<T>* item, T* widget){
        parent->setItemWidget(item, widget);
        item->updateSizeHint();
        widget->setFullyVisible(false);
    }
    int trueRow;
    T* widget;
};
