#ifndef VOLUMETINEIN_H
#define VOLUMETINEIN_H

#include <QWidget>
#include <QSlider>
#include <QVBoxLayout>
#include <QMediaPlayer>
#include <QHBoxLayout>
#include <QPushButton>
#include "widgets/hideablewidget/hideablewidget.h"
#include "slidertest.h"

class VolumeTuneIn : public QWidget
{
    Q_OBJECT
public:
    VolumeTuneIn(QWidget* parent = nullptr);
    ~VolumeTuneIn();

    void setMediaPlayer(QMediaPlayer* player);

    HiddenWidget* getHiddenWidget() const;
protected:
    void resizeEvent(QResizeEvent *event);
private:
    HiddenWidget* hiddenWidget;
    struct HiddenWidgetData
    {
        int width;
    };
    HiddenWidgetData hiddenWidgetData;
    void inSight(bool visibility);

    QHBoxLayout* layout;
    QSlider* masterVolume;

    QVBoxLayout* songLayout;
    QSlider* songVolume;
    QSlider* songSlider;
    QPushButton* playButton;
    RangeSlider* multi;


    QMediaPlayer* player;
};

#endif // VOLUMETINEIN
