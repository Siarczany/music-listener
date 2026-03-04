#include "dragwidget.h"

#include <QMouseEvent>

DragWidget::DragWidget(QWidget *parent)
    : QFrame(parent)
{
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setFrameStyle(QFrame::NoFrame);
    //setFrameStyle(QFrame::Box); // hitbox xd
    setAcceptDrops(true);
    setCursor(Qt::SizeHorCursor);
}

DragWidget::~DragWidget()
{

}

void DragWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        startPoint = event->globalPosition().toPoint();
        dragging = true;
        emit pressed();
        //qDebug() << "pressed: " << event->globalPosition().toPoint();
    }
}

void DragWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        dragging = false;
        emit released();
        //qDebug() << "released";
    }
}

void DragWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(dragging)
    {
        emit dragged(event->globalPosition().toPoint() - startPoint);
        //qDebug() << "dragged: " << event->globalPosition().toPoint() - startPoint;
    }
}
