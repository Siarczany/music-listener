#ifndef PLAYER_SCREEN_H
#define PLAYER_SCREEN_H

#include <QWidget>
#include <QSqlDatabase>
#include <QMediaPlayer>
#include <QAudioOutput>

namespace Ui {
class player_screen;
}

class PlayerScreen : public QWidget
{
    Q_OBJECT

public:
    explicit PlayerScreen(QWidget *parent = nullptr, QSqlDatabase* database = nullptr, bool isGuest = false, int userId = 0, int playlistId = 0);
    ~PlayerScreen();

private:
    Ui::player_screen *ui;
    QSqlDatabase* database;
    bool isGuest;
    int userId;
    int playlistId;

    QMediaPlayer* player;
    QAudioOutput* audioOutput;
    bool isUserSeeking = false;
    bool isPlaying = false;


    int playlistSize;
    int currentSongNumber = 0;

    QString songLength;

    void playlistInfoQuery();
    void songInfoQuery();

    float root(const int degree, const float num, const unsigned int maxIterations = 100, const float error = 1e-10);
    float powerIntFancy(const float num, const int pow);
    void setVolume();

    void pause();
    void resume();

    void setCurrentSong();
    void nextSong();
    void previousSong();

    void updateSongSlider();
    void sliderPressed();
    void sliderReleased();

    void playerStatusChanged();

};

#endif // PLAYER_SCREEN_H
