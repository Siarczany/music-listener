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
signals:
    void outOfSight(const bool visibility);
private:
    ClickableLabel* label;
    HiddenWidget* hidden;
    QWidget* widget;
    QVBoxLayout* layout;

    bool visible = true;

};

#endif // HIDEABLEWIDGET
