#pragma once

#include <QLineEdit>
#include "widgets/resizablewidget/resizeablewidget.h"

class ExampleResizable : public QObject
{
    Q_OBJECT
public:
    ExampleResizable(QWidget* parent = nullptr);
    ~ExampleResizable();
signals:
    void sizeChanged();
private:
    ResizableWidget* resizableWidget;
protected:
    void resizeEvent(QResizeEvent* event);
};
