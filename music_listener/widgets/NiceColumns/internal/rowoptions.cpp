#include "rowoptions.h"

#include <QMenu>
#include <QAction>
#include <QContextMenuEvent>

RowOptions::RowOptions(QWidget *parent) :
    QWidget(parent)
{
    /*
    menu = new QMenu(this);

    QAction* tagAction = menu->addAction("Tag");
    connect(tagAction, &QAction::triggered, this, [this](){
        emit tag(index);
    });

    QAction* editAction = menu->addAction("Edit");
    connect(editAction, &QAction::triggered, this, [this](){
        emit edit(index);
    });

    QAction* removeAction = menu->addAction("Delete");
    connect(removeAction, &QAction::triggered, this, [this](){
        emit remove(index);
    });
//*/
}

void RowOptions::setIndex(int index)
{
    this->index = index;
}

void RowOptions::setMenu(QMenu *menu)
{
    this->menu = menu;
}

void RowOptions::contextMenuEvent(QContextMenuEvent* event)
{
    if(menu)
    {
        menu->exec(event->globalPos());
    }
}
