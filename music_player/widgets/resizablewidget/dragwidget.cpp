#include "dragwidget.h"

#include <QMouseEvent>

DragWidget::DragWidget(QWidget *parent)
    : QFrame(parent)
{
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setFrameStyle(QFrame::NoFrame);
    //setFrameStyle(QFrame::Box); // hitbox xd
    //setAcceptDrops(true); // idk what this does really xd
    setCursor(Qt::SizeHorCursor); // for the user to know that this will resize things
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
    }
}

void DragWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        dragging = false;
        emit released();
    }
}

void DragWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(dragging)
    {
        emit dragged(event->globalPosition().toPoint() - startPoint);
    }
}
