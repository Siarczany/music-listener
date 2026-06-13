#pragma once

#include <QListWidget>

// my implementation of QListWidget because original works in ways I don't fully
//  like
class MyListWidget : public QListWidget
{
    Q_OBJECT
public:
    MyListWidget(QWidget* parent = nullptr);
    bool isMousePressed() const;
private:
    bool mousePressed = false;
protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
};
