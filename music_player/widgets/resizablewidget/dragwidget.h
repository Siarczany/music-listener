#ifndef DRAGWIDGET_H
#define DRAGWIDGET_H

#include <QFrame>

// widget that tracks how much the mouse was dragged
//  as well as changing the cursor to resizable icon
// q frame because I wanted to see the "hitbox" during writing it
class DragWidget : public QFrame
{
    Q_OBJECT
public:
    explicit DragWidget(QWidget *parent = nullptr);
    ~DragWidget();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
signals:
    void pressed();
    void dragged(QPoint movedAmount);
    void released();
private:
    bool dragging = false;

    // starting point of a click in global coords
    QPoint startPoint;
};

#endif // DRAGWIDGET_H
