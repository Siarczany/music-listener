#ifndef DRAGWIDGET_H
#define DRAGWIDGET_H

#include <QFrame>


class DragWidget : public QFrame
{
    Q_OBJECT
public:
    explicit DragWidget(QWidget *parent = nullptr);
    ~DragWidget();
    int index();
    void setIndex(int index);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
signals:
    void dragged(int index, int movedAmount);
private:
    int DWIndex;
    bool dragging = false;
    QPoint start_point;
};

#endif // DRAGWIDGET_H
