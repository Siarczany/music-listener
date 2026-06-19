#ifndef RESIZABLEWIDGET_H
#define RESIZABLEWIDGET_H

#include <QObject>
#include <QWidget>
#include "dragwidget.h"

// qt allows inheritance from only 1 qwiget so we can't for example
//  inherit qLabel and ResizableWidget at once so we need to be sneaky :(
// this class is supposed to be used on widgets that are inside a Form
//  because they resize 2 times the movement because the parent is centered
class ResizableWidget : public QObject
{
    Q_OBJECT
public:
    ResizableWidget(QWidget* target, QWidget* parent = nullptr);

    // call this from the target in resizeEvent to update DragWidgets positions
    void resize();
signals:
    // this ain't a QWidget so this is a normal signal xd
    void sizeChanged();

private:
    // I guess 99% of time target will be the same as parent but wwho knows
    QWidget* target;

    // resizers
    DragWidget* resizerRight;
    DragWidget* resizerLeft;

    // parent size at a start of a click
    QPoint widgetStartingSize;

    // resizer width in parent widget
    //  this doean't change the size of parent widget
    //  this kinda just takes over resizerOverlap pixels on both sides
    int resizerOverlap = 5;

    // min space the parent can be shrunk to expressed in not full width
    //  but in space of parent that is still usable
    int minSpaceToClick = 10;

    // updates the starting size during a click
    void updateStartingSize();

    // clamps the size between minimum and app window size and resized the parent
    void resizeTarget(int width);

    // updates the position of resizers because this isn't a QLayout so we do it
    //  manually
    void updateResizers();
};

#endif // RESIZABLEWIDGET
