#pragma once

#include "widgets/viewbase/itemwidgetbase.h" // ItemWidgetBase
#include "exampledata.h" // ExampleData
#include "widgets/viewbase/viewbase.h" // ViewBase
#include <QHBoxLayout> //
#include <QLabel>      //  stuff for item
#include <QPushButton> //

class ExampleItem : public ItemWidgetBase
{
    Q_OBJECT
public:
    ExampleItem(QWidget* parent = nullptr, ExampleData* data = nullptr);
    ~ExampleItem() override;
    void setFullyVisible(bool visible) override;
    void update(ModelData *data) override;
    void connectToList(ViewBase* list, int index) override;
    ItemWidgetBase* nowy(QWidget *parent, ModelData *data) override;
signals:
    deleted();
    sus();
    amogus();
private:
    QHBoxLayout* layout;
    QLabel* label;
    QPushButton* del;

};
