#pragma once

#include "widgets/viewbase/viewbase.h"
#include "widgets/resizablewidget/resizeablewidget.h"

class ListView : public ViewBase
{
    Q_OBJECT
public:
    ListView(ItemWidgetBase* factory, QWidget* parent = nullptr);
signals:
    // for deleting an item from list
    void deleted(int index);

    // resizable widget signal
    void sizeChanged();

protected:
    // for resizable widget
    void resizeEvent(QResizeEvent* event) override;

private:
    ResizableWidget* resizableWidget;
};
