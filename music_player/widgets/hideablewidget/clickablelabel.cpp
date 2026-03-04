#include "clickablelabel.h"

void ClickableLabel::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        emit pressed();
    }
}
