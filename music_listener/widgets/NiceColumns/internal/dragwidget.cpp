#include "dragwidget.h"

#include <QMouseEvent>

DragWidget::DragWidget(QWidget *parent)
    : QFrame(parent)
{
    //setMinimumSize(200, 200);
    setMinimumWidth(11);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    setFrameStyle(QFrame::VLine);
    //setFrameStyle(QFrame::Box); // hitbox xd
    setAcceptDrops(true);
}

DragWidget::~DragWidget()
{

}

int DragWidget::index()
{
    return DWIndex;
}

void DragWidget::setIndex(int index)
{
    DWIndex = index;
}

void DragWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        start_point = event->position().toPoint();
        dragging = true;
        //qDebug() << "start point at:" << start_point;
    }
    //qDebug() << "regular click" <<  event->position();
}

void DragWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        dragging = false;
    }
    //qDebug() << "stopped click " << event->position();
}

void DragWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(dragging)
    {
        //qDebug() << "moveAmount:" << (event->position() - start_point);
        //qDebug() << "nowThis:" << event->position() << "nowParent:" << mapToParent(event->position());
        //qDebug() << DWIndex << (event->position() - start_point).x();
        emit dragged(DWIndex, (event->position() - start_point).x());
        //QPoint new_pos = mapToParent(event->pos() - start_point);
        //move(new_pos);
        //qDebug() << event->position() - start_point + this->pos();
    }
    //qDebug() << "curr mouse " << event->position();
}
