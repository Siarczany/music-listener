#include "resizeablewidget.h"

ResizableWidget::ResizableWidget(QWidget *target, QWidget *parent)
    : QObject(parent)
    , target(target)
    , resizerRight(new DragWidget(target))
    , resizerLeft(new DragWidget(target))
{
    target->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    resizerRight->raise();
    resizerLeft->raise();

    connect(resizerRight, &DragWidget::pressed,
            this, &ResizableWidget::updateStartingSize);
    connect(resizerLeft, &DragWidget::pressed,
            this, &ResizableWidget::updateStartingSize);

    connect(resizerRight, &DragWidget::dragged,
            this, [this](QPoint point){
        resizeTarget(widgetStartingSize.x() + 2*point.x());
    });
    connect(resizerLeft, &DragWidget::dragged,
            this, [this](QPoint point){
        resizeTarget(widgetStartingSize.x() - 2*point.x());
    });
}

void ResizableWidget::resize()
{
    updateResizers();
    emit sizeChanged();
}

void ResizableWidget::updateStartingSize()
{
    widgetStartingSize = QPoint(target->size().width(), target->size().height());
}

void ResizableWidget::resizeTarget(int width)
{
    int availableSpace = target->window()->geometry().width();
    if(availableSpace < width)
    {
        width = availableSpace;
    }
    if(width <= 2*resizerOverlap + minSpaceToClick)
    {
        width = 2*resizerOverlap + minSpaceToClick;
    }
    target->setFixedWidth(width);
}

void ResizableWidget::updateResizers()
{
    int width = target->width();
    int height = target->height();
    resizerRight->setGeometry(width - resizerOverlap, 0,
                              resizerOverlap, height);
    resizerLeft->setGeometry(0, 0,
                             resizerOverlap, height);
}
