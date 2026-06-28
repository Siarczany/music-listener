#pragma once

#include <QSlider>

// Slider z dwoma uchwytami: dolny (min) i gorny (max).
// Jeden widget -> brak konfliktu zdarzen myszy.
class RangeSlider : public QSlider
{
    Q_OBJECT
public:
    explicit RangeSlider(Qt::Orientation orientation, QWidget *parent = nullptr);
    ~RangeSlider();

protected:
    void paintEvent(QPaintEvent* event) override;
private:
    int min = 0;
    int max = 0;
};
