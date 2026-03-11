#include "listview.h"

ListView::ListView(ItemWidgetBase *factory, QWidget *parent)
    : ViewBase(factory, parent)
{
    resizableWidget = new ResizableWidget(this, this);
    connect(resizableWidget, &ResizableWidget::sizeChanged,
            this, [this](){
                emit sizeChanged();
            });
}

void ListView::resizeEvent(QResizeEvent *event)
{
    ViewBase::resizeEvent(event);
    resizableWidget->resize();
}
