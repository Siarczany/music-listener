#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QStackedWidget>

#include <login_screen.h>
#include <register_screen.h>
#include <playlists_screen.h>
#include <testowanie.h>
#include <songs_screen.h>
#include <songs_add_screen.h>
#include <songs_edit_screen.h>
#include <songs_tag_screen.h>
#include <songs_tag_add_screen.h>
#include <playlist_add_screen.h>
#include <playlist_edit_screen.h>
#include <playlist_song_add_screen.h>
#include <playlist_song_edit_screen.h>
#include <player_screen.h>


// screen classes definitions
//class login_screen;
//class register_screen;
//class playlists_screen;
//class testowanie;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, QSqlDatabase* database = nullptr);
    ~MainWindow();

private:
    QSqlDatabase* db;
    QWidget* last_screen = nullptr;

    login_screen* login;
    register_screen* registe; // "register" is something else in qt xddd
    playlists_screen* playlists;
    testowanie* test;
    songs_screen* songs;
    songs_add_screen* songsAdd;
    SongsEditScreen* songsEdit;
    SongsTagScreen* songsTag;
    SongsTagAddScreen* songsTagAdd;
    PlaylistAddScreen* playlistAdd;
    PlaylistEditScreen* playlistEdit;
    PlaylistSongAddScreen* playlistSongAdd;
    PlaylistSongEditScreen* playlistSongEdit;
    PlayerScreen* player;

    QWidget* screen;

    void switch_screens(QWidget* current_screen);
    void show_login();
    void show_register();
    void show_playlists(bool is_guest, int user_id);
    void show_testowanie();
    void show_songs(bool is_guest, int user_id);
    void showSongsAdd(bool isGuest, int userId);
    void showSongsEdit(bool isGuest, int userId, int songId);
    void showSongsTags(bool isGuest, int userId, int songId);
    void showSongsTagAdd(bool isGuest, int userId, int songId);
    void showPlaylistAdd(bool isGuest, int userId);
    void showPlaylistEdit(bool isGuest, int userId, int playlistId);
    void showPlaylistSongAdd(bool isGuest, int userId, int playlistId);
    void showPlaylistSongEdit(bool isGuest, int userId, int playlistId, int songId);
    void showPlayer(bool isGuest, int userId, int playlistId);

    template<typename app_screen>
    void show_screen()
    {
        screen = new app_screen(this, db);
        setCentralWidget(screen);
        if(last_screen != nullptr)
        {
            last_screen->deleteLater();
        }
        last_screen = screen;
    }
};
#endif // MAINWINDOW_H
