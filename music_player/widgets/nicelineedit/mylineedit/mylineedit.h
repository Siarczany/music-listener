#ifndef RESIZABLELINEEDIT_H
#define RESIZABLELINEEDIT_H

#include <QLineEdit>
#include <QMouseEvent>
#include "widgets/resizablewidget/resizeablewidget.h"

// normal line edit but you are able to resize it
class ResizableLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    ResizableLineEdit(QWidget* parent = nullptr);
    ~ResizableLineEdit();

signals:
    // signal for uppper widget
    void sizeChanged();

private:
    // doer of resizing
    ResizableWidget* resizableWidget;

protected:
    // for resizableWidget
    void resizeEvent(QResizeEvent *event) override;

    // i wanted to to something akin to scrollable label but with text in the lineedit but idk if it's possible
    //  so this just moves the cursor
    void wheelEvent(QWheelEvent* event) override;
};

#endif // RESIZABLELINEEDIT_H
