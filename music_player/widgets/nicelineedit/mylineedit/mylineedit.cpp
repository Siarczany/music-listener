#include "mylineedit.h"



ResizableLineEdit::ResizableLineEdit(QWidget *parent)
    : QLineEdit(parent)
    , resizableWidget(new ResizableWidget(this, this))
{
    connect(resizableWidget, &ResizableWidget::sizeChanged,
                  this, [this](){
        emit sizeChanged();
    });
}

ResizableLineEdit::~ResizableLineEdit()
{

}

void ResizableLineEdit::resizeEvent(QResizeEvent *event)
{
    QLineEdit::resizeEvent(event);
    resizableWidget->resize();
}

void ResizableLineEdit::wheelEvent(QWheelEvent *event)
{
    if(event->angleDelta().y() > 0)
    {
        cursorForward(false, 1);
    }
    else
    {
        cursorBackward(false, 1);
    }

    event->accept();
}



