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
    HideableWidget(HiddenWidget* widget, QWidget* parent = nullptr);
    ~HideableWidget();

    void setText(const QString& text);
    QWidget* getWidget() const;
private:
    ClickableLabel* label;
    HiddenWidget* widget;
    QVBoxLayout* layout;

    bool visible = true;

};

#endif // HIDEABLEWIDGET
