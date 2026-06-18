#pragma once

#include <QVBoxLayout>
#include "exampleview.h"

class ExampleList : public QWidget
{
    Q_OBJECT
public:
    ExampleList(QWidget* parent = nullptr);
    ~ExampleList();
private:
    QVBoxLayout* layout;

    Model* model;
    ExampleView* view;

    void refresh();
};
