#include "mainwindow.h"

#include <QStackedWidget>
#include <QSettings>

MainWindow::MainWindow(QWidget *parent, QSqlDatabase* database)
    : QMainWindow(parent)
    , db(database)
{
    QSettings settings("settings.ini", QSettings::IniFormat);
    settings.setValue("lastUser", "");

    if(settings.value("lastUser").toString() == "")
    {
        //show_screen<login_screen>();
        show_login();
        //show_register();
        //show_testowanie();
        //show_playlists(false, 1);
        //show_songs(false, 1);
        //showSongsAdd(false, 0);
        //showPlaylistAdd(true, 0);
        //showPlaylistEdit(true, 0, 1);
        //showPlayer(true, 0, 0);
    }

    //login = new login_screen(this, database);

    resize(800, 600);

    //setCentralWidget(screens);
    //screens->addWidget(login);
    //screens->setCurrentWidget(login);
    //show_login();
    //show_screen<login_screen>();
}

MainWindow::~MainWindow()
{

}

void MainWindow::updateIsGuest(bool isGuest)
{
    this->isGuest = isGuest;
}

void MainWindow::updateUserId(int userId)
{
    this->userId = userId;
}

void MainWindow::updateSongId(int songId)
{
    this->songId = songId;
}

void MainWindow::updatePlaylistId(int playlistId)
{
    this->playlistId = playlistId;
}



void MainWindow::switch_screens(QWidget* current_screen)
{
    setCentralWidget(current_screen);
    if(last_screen != nullptr)
    {
        last_screen->deleteLater();
        qDebug() << "deleting later: " << last_screen;


    }
    last_screen = current_screen;
}

void MainWindow::show_login()
{
    login = new login_screen(this, db);
    connect(login, &login_screen::updateIsGuest, this, updateIsGuest);
    connect(login, &login_screen::updateUserId, this, updateUserId);

    connect(login, login->to_register_screen, this, show_register);
    connect(login, login->to_playlists_screen, this, show_playlists);

    switch_screens(login);

    printStuff();
}

void MainWindow::show_register()
{
    registe = new register_screen(this, db);
    connect(registe, registe->to_login_screen, this, show_login);

    switch_screens(registe);

    printStuff();
}

void MainWindow::show_playlists()
{
    playlists = new playlists_screen(this, db, isGuest, userId);
    connect(playlists, playlists->to_login_screen, this, show_login);
    connect(playlists, playlists->to_songs_screen, this, show_songs);
    connect(playlists, &playlists_screen::toPlaylistAddScreen, this, showPlaylistAdd);
    connect(playlists, &playlists_screen::toPlaylistEditScreen, this, showPlaylistEdit);
    connect(playlists, &playlists_screen::toPlayerScreen, this, showPlayer);

    switch_screens(playlists);

    printStuff();
}

void MainWindow::show_testowanie()
{
    test = new testowanie(this);

    switch_screens(test);

    printStuff();
}

void MainWindow::show_songs()
{
    songs = new songs_screen(this, db, isGuest, userId);
    connect(songs, &songs_screen::updateSongsId, this, updateSongId);

    connect(songs, songs->to_playlists_screen, this, show_playlists);
    connect(songs, &songs_screen::toSongsAddScreen, this, showSongsAdd);
    connect(songs, &songs_screen::toSongsEditScreen, this, showSongsEdit);
    connect(songs, &songs_screen::toSongsTagScreen, this, showSongsTags);

    switch_screens(songs);

    printStuff();
}

void MainWindow::showSongsAdd()
{
    songsAdd = new songs_add_screen(this, db, isGuest, userId);


    connect(songsAdd, &songs_add_screen::toSongsScreen, this, show_songs);

    switch_screens(songsAdd);

    printStuff();
}

void MainWindow::showSongsEdit()
{
    songsEdit = new SongsEditScreen(this, db, isGuest, userId, songId);
    connect(songsEdit, &SongsEditScreen::updateSongId, this, updateSongId);

    connect(songsEdit, &SongsEditScreen::toSongsScreen, this, show_songs);

    switch_screens(songsEdit);

    printStuff();
}

void MainWindow::showSongsTags()
{
    songsTag = new SongsTagScreen(this, db, isGuest, userId, songId);
    connect(songsTag, &SongsTagScreen::updateSongId, this, updateSongId);

    connect(songsTag, SongsTagScreen::toSongsScreen, this, show_songs);
    connect(songsTag, &SongsTagScreen::toSongsTagAddScreen, this, showSongsTagAdd);

    switch_screens(songsTag);

    printStuff();
}

void MainWindow::showSongsTagAdd(bool isGuest, int userId, int songId)
{
    songsTagAdd = new SongsTagAddScreen(this, db, isGuest, userId, songId);
    connect(songsTagAdd, &SongsTagAddScreen::toSongsTagsScreen, this, showSongsTags);

    switch_screens(songsTagAdd);

    printStuff();
}

void MainWindow::showPlaylistAdd(bool isGuest, int userId)
{
    playlistAdd = new PlaylistAddScreen(this, db, isGuest, userId);
    connect(playlistAdd, &PlaylistAddScreen::toPlaylistsScreen, this, show_playlists);

    switch_screens(playlistAdd);

    printStuff();
}

void MainWindow::showPlaylistEdit(bool isGuest, int userId, int playlistId)
{
    playlistEdit = new PlaylistEditScreen(this, db, isGuest, userId, playlistId);
    connect(playlistEdit, &PlaylistEditScreen::toPlaylistsScreen, this, show_playlists);
    connect(playlistEdit, &PlaylistEditScreen::toPlaylistsSongAddScreen, this, showPlaylistSongAdd);
    connect(playlistEdit, &PlaylistEditScreen::toPlaylistsSongEditScreen, this, showPlaylistSongEdit);

    switch_screens(playlistEdit);

    printStuff();
}

void MainWindow::showPlaylistSongAdd(bool isGuest, int userId, int playlistId)
{
    playlistSongAdd = new PlaylistSongAddScreen(this, db, isGuest, userId, playlistId);
    connect(playlistSongAdd, &PlaylistSongAddScreen::toPlaylistEditScreen, this, showPlaylistEdit);

    switch_screens(playlistSongAdd);

    printStuff();
}

void MainWindow::showPlaylistSongEdit(bool isGuest, int userId, int playlistId, int songId)
{
    playlistSongEdit = new PlaylistSongEditScreen(this, db, isGuest, userId, playlistId, songId);
    connect(playlistSongEdit, &PlaylistSongEditScreen::toPlaylistScreen, this, showPlaylistEdit);

    switch_screens(playlistSongEdit);

    printStuff();
}

void MainWindow::showPlayer(bool isGuest, int userId, int playlistId)
{
    player = new PlayerScreen( this, db, isGuest, userId, playlistId);

    switch_screens(player);

    printStuff();
}

void MainWindow::printStuff()
{
    qDebug() << "isGuest:" << isGuest;
    qDebug() << "userId:" << userId;
    qDebug() << "songId:" << songId;
    qDebug() << "playlistId:" << playlistId;
}

