#pragma once

#include "widgets/viewbase/viewbase.h" // ViewBase

class ExampleView : public ViewBase
{
    Q_OBJECT
public:
    ExampleView(ItemWidgetBase* factory, QWidget* parent = nullptr);
signals:
    void deleted(int index);
    void sus();
    void amogus();
};
