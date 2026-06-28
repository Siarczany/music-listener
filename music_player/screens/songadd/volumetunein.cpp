#include "volumetunein.h"


VolumeTuneIn::VolumeTuneIn(QWidget *parent)
    : QWidget(parent)
    , layout(new QHBoxLayout(this))
    , songLayout(new QVBoxLayout())
    , masterVolume(new QSlider(Qt::Vertical, this))
    , songVolume(new QSlider(Qt::Horizontal, this))
    , songSlider(new QSlider(Qt::Horizontal, this))
    , playButton(new QPushButton(this))
    , multi(new RangeSlider(Qt::Horizontal, this))
    , hiddenWidget(new HiddenWidget(this, this))
{
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);

    songLayout->setSpacing(0);
    songLayout->setContentsMargins(0, 0, 0, 0);

    playButton->setText("Play");

    songLayout->addWidget(songVolume);
    songLayout->addWidget(songSlider);
    songLayout->addWidget(playButton, 0, Qt::AlignHCenter);
    songLayout->addWidget(multi);

    layout->addLayout(songLayout);
    layout->addWidget(masterVolume);

    connect(hiddenWidget, &HiddenWidget::inSight,
            this, &VolumeTuneIn::inSight);
}

VolumeTuneIn::~VolumeTuneIn()
{

}

void VolumeTuneIn::setMediaPlayer(QMediaPlayer *player)
{
    this->player = player;
}

HiddenWidget *VolumeTuneIn::getHiddenWidget() const
{
    return hiddenWidget;
}

void VolumeTuneIn::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    emit hiddenWidget->sizeChanged();
}

void VolumeTuneIn::inSight(bool visibility)
{
    if(visibility == false)
    {
        hiddenWidgetData.width = width();
    }
    else
    {
        setFixedWidth(hiddenWidgetData.width);
    }
    setVisible(visibility);
}
