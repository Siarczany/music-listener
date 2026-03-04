#include "resizablelineedit.h"



ResizableLineEdit::ResizableLineEdit(QWidget *parent)
    : QLineEdit(parent)
    , resizerRight(new DragWidget(this))
    , resizerLeft(new DragWidget(this))
    , layout(new QHBoxLayout(this))
{
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    resizerRight->raise();
    resizerLeft->raise();

    connect(resizerRight, &DragWidget::pressed, this, &ResizableLineEdit::updateLineEditStartingSize);
    connect(resizerLeft, &DragWidget::pressed, this, &ResizableLineEdit::updateLineEditStartingSize);

    connect(resizerRight, &DragWidget::dragged, this, [this](QPoint point)
            {
        resizeLineEdit(lineEditStartingSize.x() + 2*point.x());
    });
    connect(resizerLeft, &DragWidget::dragged, this, [this](QPoint point)
            {
        resizeLineEdit(lineEditStartingSize.x() - 2*point.x());
    });
}

ResizableLineEdit::~ResizableLineEdit()
{

}

void ResizableLineEdit::updateLineEditStartingSize()
{
    lineEditStartingSize = QPoint(size().width(), size().height());
}

void ResizableLineEdit::resizeLineEdit(int width)
{
    int availableSpace = window()->geometry().width();
    if(availableSpace < width)
    {
        width = availableSpace;
    }
    if(width <= 2*resizerOverlap + minSpaceToClick)
    {
        width = 2*resizerOverlap + minSpaceToClick;
    }
    setFixedWidth(width);
}

void ResizableLineEdit::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    int overlap = 5;

    resizerRight->setGeometry(
        width() - overlap, 0,
        overlap, height());

    resizerLeft->setGeometry(
        0, 0,
        overlap, height());

    emit sizeChanged();
}

void ResizableLineEdit::wheelEvent(QWheelEvent *event)
{
    //Q_D(QLineEdit);  // dostęp do d-pointera -> QLineEditPrivate*

    //int delta = event->angleDelta().y();
    //int step = 20;

    //int newOffset = d->hscroll + (delta < 0 ? step : -step);
    //d->setScrollOffset(newOffset);  // bezpośrednie przesunięcie widoku

    //update();
    if(event->angleDelta().y() > 0)
    {
        cursorForward(false, 1);
    }
    else
    {
        cursorBackward(false, 1);
    }
    //qDebug() << event->angleDelta().y();

    event->accept();
}



