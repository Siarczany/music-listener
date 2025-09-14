#include "headeroptions.h"

#include <QMenu>
#include <QAction>
#include <QMouseEvent>

HeaderOptions::HeaderOptions(QWidget *parent, QVector<column>* vec) :
    QWidget(parent)
    , contents(vec)
{

}

void HeaderOptions::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);

    if(contents != nullptr)
    {
        for(int i = 0; i<contents->size(); i++)
        {
            QAction* action = menu.addAction((*contents)[i].header());
            action->setCheckable(true);
            action->setChecked((*contents)[i].active());

            connect(action, &QAction::toggled, this, [this, i](bool checked){
                emit setActive(i, checked);
            });
        }
    }

    menu.exec(event->globalPos());
}
