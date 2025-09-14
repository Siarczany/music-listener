#ifndef PLAYLIST_SONG_ADD_SCREEN_H
#define PLAYLIST_SONG_ADD_SCREEN_H

#include <QWidget>
#include <QSqlDatabase>
#include "widgets/NiceColumns/nicecolumns.h"
#include <QPushButton>

namespace Ui {
class playlist_song_add_screen;
}

class PlaylistSongAddScreen : public QWidget
{
    Q_OBJECT

public:
    explicit PlaylistSongAddScreen(QWidget *parent = nullptr, QSqlDatabase* database = nullptr, bool isGuest = true, int userId = 0, int playlistId = 0);
    ~PlaylistSongAddScreen();

signals:
    toPlaylistEditScreen(bool isGuest, int userId = 0, int playlistId = 0);

private:
    Ui::playlist_song_add_screen *ui;
    QSqlDatabase* database;
    bool isGuest;
    int userId;
    int playlistId;

    NiceColumns* nic;
    QPushButton* back_pb;

    void setupTopWidget();
    void setupNiceColumns();
    void setupBody();

    void addSongQuery(int songId);

    void showPlaylistEdit();
};

#endif // PLAYLIST_SONG_ADD_SCREEN_H
