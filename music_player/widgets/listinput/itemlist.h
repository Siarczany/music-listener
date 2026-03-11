#pragma once

#include "widgets/hideablewidget/hideablewidget.h"
#include "widgets/viewbase/viewbase.h"
#include "listview.h"
class ItemList : public QWidget
{
    Q_OBJECT
public:
    ItemList(QWidget* parent = nullptr);
    ~ItemList();

    HiddenWidget* getHiddenWidget() const;
    int count() const;
    void addFirst(const QString& text);
    void add(const QString& text);
    void setLabel(const QString& text);
signals:
    void sizeChanged();
protected:
    void resizeEvent(QResizeEvent *event) override;
private:
    QVBoxLayout* layout;
    HiddenWidget* hiddenWidget;
    Model* model;
    ListView* view;

    QString labelText;

    bool firstLockedIn = false;
    void refresh();
};
