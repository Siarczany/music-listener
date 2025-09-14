#ifndef PLAYLIST_EDIT_SCREEN_H
#define PLAYLIST_EDIT_SCREEN_H

#include <QWidget>
#include <QSqlDatabase>
#include <QLabel>
#include <QPushButton>
#include "widgets/NiceColumns/nicecolumns.h"

namespace Ui {
class Playlist_Edit_Screen;
}

class PlaylistEditScreen : public QWidget
{
    Q_OBJECT

public:
    explicit PlaylistEditScreen(QWidget *parent = nullptr, QSqlDatabase* database = nullptr, bool isGuest = true, int userId = 0, int playlistId = 0);

    ~PlaylistEditScreen();

signals:
    toPlaylistsScreen(bool isGuest, int userId = 0);
    toPlaylistsSongAddScreen(bool isGuest, int userId = 0, int playlistId = 0);
    toPlaylistsSongEditScreen(bool isGuest, int userId = 0, int playlistId = 0, int songId = 0);

private:
    Ui::Playlist_Edit_Screen *ui;
    QSqlDatabase* database;
    bool isGuest;
    int userId;
    int playlistId;

    QLabel* name_l;
    QPushButton* back_pb;
    NiceColumns* nic;
    QLabel* songs_l;
    QPushButton* add_pb;

    void setupTopWidget();
    void nameQuery();

    void setupMiddleWidget();
    void setupColumns();
    void setupBody();
    void removeSong(int index);

    void showPlaylists();
    void showPlaylistsSongAdd();
};

#endif // PLAYLIST_EDIT_SCREEN_H
