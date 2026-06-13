#include "mylistwidget.h"

#include <QMouseEvent>
#include <QScrollBar>

MyListWidget::MyListWidget(QWidget *parent)
    : QListWidget(parent)
{
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
}

bool MyListWidget::isMousePressed() const
{
    return mousePressed;
}

void MyListWidget::mousePressEvent(QMouseEvent *event)
{
    mousePressed = true;
    QListWidget::mousePressEvent(event);
}

void MyListWidget::mouseReleaseEvent(QMouseEvent *event)
{
    mousePressed = false;
    QListWidget::mouseReleaseEvent(event);
}

void MyListWidget::wheelEvent(QWheelEvent *event)
{
    QListWidget::wheelEvent(event);
}
