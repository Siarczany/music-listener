#ifndef RESIZABLELINEEDIT_H
#define RESIZABLELINEEDIT_H

#include <QWidget>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QMouseEvent>
#include "dragwidget.h"

class ResizableLineEdit : public QWidget
{
    Q_OBJECT

public:
    ResizableLineEdit(QWidget* parent = nullptr);
    ~ResizableLineEdit();

    const QString text();

signals:
    void sizeChanged();

private:
    QLineEdit* lineEdit;
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
};

#endif // RESIZABLELINEEDIT_H
