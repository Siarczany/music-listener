#ifndef VOLUMETINEIN_H
#define VOLUMETINEIN_H

#include <QWidget>
#include <QSlider>
#include <QVBoxLayout>
#include <QMediaPlayer>
#include <QHBoxLayout>
#include <QPushButton>

class VolumeTuneIn : public QWidget
{
    Q_OBJECT
public:
    VolumeTuneIn(QWidget* parent = nullptr);
    ~VolumeTuneIn();

    void setMediaPlayer(QMediaPlayer* player);
private:
    QHBoxLayout* layout;
    QSlider* masterVolume;

    QVBoxLayout* songLayout;
    QSlider* songVolume;
    QSlider* songSlider;
    QPushButton* playButton;

    QMediaPlayer* player;
};

#endif // VOLUMETINEIN
