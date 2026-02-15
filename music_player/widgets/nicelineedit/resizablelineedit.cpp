#include "resizablelineedit.h"


ResizableLineEdit::ResizableLineEdit(QWidget *parent)
    : QWidget(parent)
    , lineEdit(new QLineEdit(this))
    , resizerRight(new DragWidget(this))
    , resizerLeft(new DragWidget(this))
    , layout(new QHBoxLayout(this))
{
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    layout->addWidget(lineEdit);

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

const QString ResizableLineEdit::text()
{
    return lineEdit->text();
}

void ResizableLineEdit::updateLineEditStartingSize()
{
    lineEditStartingSize = QPoint(lineEdit->size().width(), lineEdit->size().height());
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
    lineEdit->setFixedWidth(width);
}

void ResizableLineEdit::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    int overlap = 5;

    resizerRight->setGeometry(
        lineEdit->width() - overlap, 0,
        overlap, lineEdit->height());

    resizerLeft->setGeometry(
        0, 0,
        overlap, lineEdit->height());

    emit sizeChanged();
}



