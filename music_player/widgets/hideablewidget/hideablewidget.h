#ifndef HIDEABLEWIDGET_H
#define HIDEABLEWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include "clickablelabel.h"
#include "hiddenwidget.h"

class HideableWidget : public QWidget
{
    Q_OBJECT
public:
    HideableWidget(QWidget* widget, HiddenWidget* hidden, QWidget* parent = nullptr);
    ~HideableWidget();

    void setText(const QString& text);
    HiddenWidget* getWidget() const;
    void setInSight(const bool visibility);
    void setInSightFull(const bool visibility);
signals:
    //void inSight(const bool visibility);
private:
    ClickableLabel* label;
    //int hiddenWidth = 100;
    int visibleWidth = 250;

    HiddenWidget* hidden;
    QWidget* widget;
    QVBoxLayout* layout;

    bool visible = true;
    bool visibleFull = true;

};

#endif // HIDEABLEWIDGET
