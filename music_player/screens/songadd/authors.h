#ifndef SONGADD_AUTHORSLIST_H
#define SONGADD_AUTHORSLIST_H

#include "widgets/hideablewidget/hiddenwidget.h"
#include <QScrollArea>
#include "widgets/hideablewidget/hideablewidget.h"
#include "widgets/viewbase/viewbase.h"
#include <QPushButton>
#include "widgets/resizablewidget/resizeablewidget.h"

class Author : public ModelData
{
public:
    QString name;
};

class AuthorItem : public ItemWidgetBase
{
    Q_OBJECT
public:
    AuthorItem(QWidget* parent = nullptr, ModelData* data = nullptr);
    ~AuthorItem() override;

    void setFullyVisible(bool visible) override;

    void update(ModelData* data) override;

    void connectToList(ViewBase* list, int index) override;

    ItemWidgetBase* nowy(QWidget *parent, ModelData *data) override;
signals:
    void deleted();
private:
    QHBoxLayout* layout;
    QLabel* text;
    QPushButton* del;
};

class  AuthorsView : public ViewBase
{
    Q_OBJECT
public:
    //using ViewBase::ViewBase;
    AuthorsView(ItemWidgetBase* factory, QWidget* parent = nullptr);
signals:
    void deleted(int index);
    void sizeChanged();
protected:
    void resizeEvent(QResizeEvent* event) override;
private:
    ResizableWidget* resizableWidget;
};

class AuthorsList : public QWidget
{
    Q_OBJECT
public:
    AuthorsList(QWidget* parent = nullptr);
    ~AuthorsList();

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
    //QVBoxLayout* layout;
    AuthorsView* view;


    bool firstLockedIn = false;
    void refresh();
};

#endif // SONGADD_AUTHORSLIST




