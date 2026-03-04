#ifndef RESIZABLELINEEDIT_H
#define RESIZABLELINEEDIT_H

#include <QWidget>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QMouseEvent>
#include "dragwidget.h"
#include <private/qlineedit_p.h>

class ResizableLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    ResizableLineEdit(QWidget* parent = nullptr);
    ~ResizableLineEdit();

signals:
    void sizeChanged();

private:
    DragWidget* resizerRight;
    DragWidget* resizerLeft;
    QHBoxLayout* layout;

    QPoint lineEditStartingSize;
    void updateLineEditStartingSize();
    int resizerOverlap = 5;
    int minSpaceToClick = 10;
    void resizeLineEdit(int width);

protected:
    void resizeEvent(QResizeEvent *event) override;
    void wheelEvent(QWheelEvent* event) override;
};

#endif // RESIZABLELINEEDIT_H
