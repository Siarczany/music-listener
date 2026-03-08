#ifndef RESIZABLELINEEDIT_H
#define RESIZABLELINEEDIT_H

#include <QLineEdit>
#include <QMouseEvent>
//#include "dragwidget.h"
#include "widgets/resizablewidget/resizeablewidget.h"

class ResizableLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    ResizableLineEdit(QWidget* parent = nullptr);
    ~ResizableLineEdit();

signals:
    void sizeChanged();

private:
    ResizableWidget* resizableWidget;
protected:
    void resizeEvent(QResizeEvent *event) override;
    void wheelEvent(QWheelEvent* event) override;
};

#endif // RESIZABLELINEEDIT_H
