#include "clickablelabel.h"

ClickableLabel::ClickableLabel(QWidget *parent)
    : ScrollableLabel(parent)
{
    setCursor(Qt::PointingHandCursor);
}

void ClickableLabel::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        emit pressed();
    }
}
