#include "playlistlabel.h"

#include <QMouseEvent>
#include <QMenu>

PlaylistLabel::PlaylistLabel(QWidget *parent) :
    QLabel(parent)
{

}

PlaylistLabel::~PlaylistLabel()
{

}

void PlaylistLabel::setText(const QString text)
{
    QLabel::setText(text);
}

void PlaylistLabel::setMenu(QMenu *menu)
{
    this->menu = menu;
}

void PlaylistLabel::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        emit pressed();
    }
}

void PlaylistLabel::contextMenuEvent(QContextMenuEvent *event)
{
    if(menu)
    {
        menu->exec(event->globalPos());
    }
}
