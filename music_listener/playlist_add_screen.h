#ifndef PLAYLIST_ADD_SCREEN_H
#define PLAYLIST_ADD_SCREEN_H

#include <QWidget>
#include <QSqlDatabase>

namespace Ui {
class playlist_add_screen;
}

class PlaylistAddScreen : public QWidget
{
    Q_OBJECT

public:
    explicit PlaylistAddScreen(QWidget *parent = nullptr, QSqlDatabase* db = nullptr, bool isGuest = true, int userId = 0);
    ~PlaylistAddScreen();

signals:
    toPlaylistsScreen(bool isGuest, int userId = 0);

private:
    Ui::playlist_add_screen *ui;
    QSqlDatabase* database;
    bool isGuest;
    int userId;

    bool emptyName = false;

    void addPlaylist();
    void addQuery();

    void showPlaylistsScreen();
};

#endif // PLAYLIST_ADD_SCREEN_H
