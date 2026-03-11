#pragma once

#include "widgets/viewbase/viewbase.h"
#include "widgets/resizablewidget/resizeablewidget.h"
class ListView : public ViewBase
{
    Q_OBJECT
public:
    ListView(ItemWidgetBase* factory, QWidget* parent = nullptr);
signals:
    void deleted(int index);
    void sizeChanged();
protected:
    void resizeEvent(QResizeEvent* event) override;
private:
    ResizableWidget* resizableWidget;
};
