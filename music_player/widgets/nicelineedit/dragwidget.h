#ifndef DRAGWIDGET_H
#define DRAGWIDGET_H

#include <QFrame>

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
    QPoint startPoint;
};

#endif // DRAGWIDGET_H
