#include "volumetunein.h"


VolumeTuneIn::VolumeTuneIn(QWidget *parent)
    : QWidget(parent)
    , layout(new QHBoxLayout(this))
    , songLayout(new QVBoxLayout())
    , masterVolume(new QSlider(Qt::Vertical, this))
    , songVolume(new QSlider(Qt::Horizontal, this))
    , songSlider(new QSlider(Qt::Horizontal, this))
    , playButton(new QPushButton(this))
{
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);

    songLayout->setSpacing(0);
    songLayout->setContentsMargins(0, 0, 0, 0);

    playButton->setText("Play");

    songLayout->addWidget(songVolume);
    songLayout->addWidget(songSlider);
    songLayout->addWidget(playButton, 0, Qt::AlignHCenter);

    layout->addLayout(songLayout);
    layout->addWidget(masterVolume);
}

VolumeTuneIn::~VolumeTuneIn()
{

}

void VolumeTuneIn::setMediaPlayer(QMediaPlayer *player)
{
    this->player = player;
}
