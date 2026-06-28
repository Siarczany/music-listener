#include "slidertest.h"
#include <QStylePainter>
#include <QStyleOptionSlider>

RangeSlider::RangeSlider(Qt::Orientation orientation, QWidget *parent)
    : QSlider(orientation, parent)
{

}

RangeSlider::~RangeSlider()
{

}

void RangeSlider::paintEvent(QPaintEvent *event)
{
    QStylePainter painter(this);
    QStyleOptionSlider opt;
    initStyleOption(&opt);

    //opt.sliderValue = 0;
    //opt.sliderPosition = 0;
    opt.subControls = QStyle::SC_SliderGroove;
    painter.drawComplexControl(QStyle::CC_Slider, opt);

    opt.subControls = QStyle::SC_SliderHandle;
    opt.sliderPosition = 10;
    opt.sliderValue = 10;
    painter.drawComplexControl(QStyle::CC_Slider, opt);

    opt.subControls = QStyle::SC_SliderHandle;
    opt.sliderPosition = 80;
    opt.sliderValue = 80;
    painter.drawComplexControl(QStyle::CC_Slider, opt);
}
