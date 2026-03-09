#ifndef LISTINPUT_H
#define LISTINPUT_H

#include <QWidget>
#include <QVBoxLayout>
#include "widgets/viewbase/viewbase.h"
#include <QLabel>
#include <QPushButton>

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
    void deleted();
private:
    QHBoxLayout* layout;
    QLabel* label;
    QPushButton* del;
};

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


#include "widgets/hideablewidget/hideablewidget.h"
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
signals:
    void sizeChanged();
protected:
    void resizeEvent(QResizeEvent *event) override;
private:
    QVBoxLayout* layout;
    HiddenWidget* hiddenWidget;
    Model* model;
    ListView* view;

    bool firstLockedIn = false;
    void refresh();
};


#include "widgets/nicelineedit/nicelineedit.h"
class ListInput : public QWidget
{
    Q_OBJECT
public:
    ListInput(QWidget* parent = nullptr);
    ~ListInput();

private:
    QVBoxLayout* layout;
    NiceLineEdit* input;
    SuggestionLineEdit* suggestionInput;
    ItemList* list;
    HideableWidget* hideable;
};

#endif // LISTINPUT
