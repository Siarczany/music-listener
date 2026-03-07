#pragma once

#include <QListWidget>

class MyListWidget : public QListWidget
{
    Q_OBJECT
public:
    //using QListWidget::QListWidget;
    MyListWidget(QWidget* parent = nullptr);
    bool isMousePressed() const;
signals:
    void pressedd(); // pressed to jakiś inny sygnał mi to mói clazy
    void released();
private:
    bool mousePressed = false;
protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
};
