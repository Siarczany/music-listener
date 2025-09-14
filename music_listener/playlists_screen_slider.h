#ifndef PLAYLISTS_SCREEN_SLIDER_H
#define PLAYLISTS_SCREEN_SLIDER_H

#include <QWidget>
#include <QBoxLayout>
#include <QFrame>

class sliding_widget: public QFrame
{
    Q_OBJECT

public:
    sliding_widget(QWidget* parent = nullptr
                   , QGridLayout* layout = nullptr
                   , QWidget* screen_1 = nullptr
                   , QWidget* screen_2 = nullptr);
    ~sliding_widget();

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

    void setExtraSpace(int space);
    int extraSpace() const;

private:
    bool dragging;
    QPoint start_point;
    QWidget* screen_1;
    QWidget* screen_2;
    int extra_space = 0;

    QGridLayout* layout;
};

#endif // PLAYLISTS_SCREEN_SLIDER_H
