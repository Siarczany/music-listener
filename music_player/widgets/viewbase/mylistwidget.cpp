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
    //emit pressedd();
    mousePressed = true;
    QListWidget::mousePressEvent(event);
}

void MyListWidget::mouseReleaseEvent(QMouseEvent *event)
{
    //emit released();
    mousePressed = false;
    QListWidget::mouseReleaseEvent(event);
}

void MyListWidget::wheelEvent(QWheelEvent *event)
{
    //qDebug() << "scroll";
    //scroll(0, -1);
    //verticalScrollBar()->setValue(
    //    verticalScrollBar()->value() - event->angleDelta().y()
    //    );
    //qDebug() << verticalScrollBar()->value();
    //qDebug() << viewport()->height();

    //QListWidgetItem* itemm = item(0);
    //if(itemm != nullptr)
    //{
    //    qDebug() << itemm->sizeHint().height() << "*" << count() << "=" <<
    //        itemm->sizeHint().height()* count() - viewport()->height();
    //}
    QListWidget::wheelEvent(event);
}
