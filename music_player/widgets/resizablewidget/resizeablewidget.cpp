#include "resizeablewidget.h"

ResizableWidget::ResizableWidget(QWidget *target, QWidget *parent)
    : QObject(parent)
    , target(target)
    , resizerRight(new DragWidget(target))
    , resizerLeft(new DragWidget(target))
{
    target->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    // put display/widget hitbox on the very top co we can click the overlapping area
    //  and we will click this widget
    resizerRight->raise();
    resizerLeft->raise();

    // save starting size during click
    connect(resizerRight, &DragWidget::pressed,
            this, &ResizableWidget::updateStartingSize);
    connect(resizerLeft, &DragWidget::pressed,
            this, &ResizableWidget::updateStartingSize);

    // this is supposed to be in Form so multiplication by 2 because centered
    connect(resizerRight, &DragWidget::dragged,
            this, [this](QPoint point){
        resizeTarget(widgetStartingSize.x() + 2*point.x());
    });
    connect(resizerLeft, &DragWidget::dragged,
            this, [this](QPoint point){
        resizeTarget(widgetStartingSize.x() - 2*point.x());
    });
}

// widget just changed size so update resizers and emit because maybe up the line
//  you want to resize something other as well
void ResizableWidget::resize()
{
    updateResizers();
    emit sizeChanged();
}

void ResizableWidget::updateStartingSize()
{
    // .height() isn't used but maybe someday resizing the bottom of a widget xd
    widgetStartingSize = QPoint(target->size().width(), target->size().height());
}

void ResizableWidget::resizeTarget(int width)
{
    // size of the window because I don't want to resize things over the window size
    int availableSpace = target->window()->geometry().width();

    // clamp width between window size and min size
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

    // setGeometry takes in x and y as in start of the widget inside the parent
    //  not global coords
    // and the other two numbers is the size of this widget
    resizerRight->setGeometry(width - resizerOverlap, 0,
                              resizerOverlap, height);
    resizerLeft->setGeometry(0, 0,
                             resizerOverlap, height);
}
