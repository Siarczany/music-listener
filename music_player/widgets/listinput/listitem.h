#pragma once

#include "widgets/viewbase/viewbase.h"
#include <QLabel>
#include <QPushButton>

// list item holds just a text
class ItemData : public ModelData
{
public:
    QString name;
};

class ListItem : public ItemWidgetBase
{
    Q_OBJECT
public:
    ListItem(QWidget* parent = nullptr, ModelData* data = nullptr);
    ~ListItem() override;
    void setFullyVisible(bool visible) override;
    void update(ModelData *data) override;
    void connectToList(ViewBase *list, int index) override;
    ItemWidgetBase* nowy(QWidget *parent, ModelData *data) override;
signals:
    // we want the ability to delete things from a list
    void deleted();

private:
    QHBoxLayout* layout;
    QLabel* label;
    QPushButton* del;
};
