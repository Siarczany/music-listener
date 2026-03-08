#ifndef RESIZABLEWIDGET_H
#define RESIZABLEWIDGET_H

#include <QObject>
#include <QWidget>
#include "dragwidget.h"

class ResizableWidget : public QObject
{
    Q_OBJECT
public:
    ResizableWidget(QWidget* target, QWidget* parent = nullptr);

    void resize();
signals:
    void sizeChanged();

private:
    QWidget* target;
    DragWidget* resizerRight;
    DragWidget* resizerLeft;
    QPoint widgetStartingSize;

    int resizerOverlap = 5;
    int minSpaceToClick = 10;
    void updateStartingSize();
    void resizeTarget(int width);
    void updateResizers();
};

#endif // RESIZABLEWIDGET
