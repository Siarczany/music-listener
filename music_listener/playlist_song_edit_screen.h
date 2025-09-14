#ifndef PLAYLIST_SONG_EDIT_SCREEN_H
#define PLAYLIST_SONG_EDIT_SCREEN_H

#include <QWidget>
#include <QSqlDatabase>
#include "widgets/suggestionlineedit.h"

namespace Ui {
class playlist_song_edit_screen;
}

class PlaylistSongEditScreen : public QWidget
{
    Q_OBJECT

public:
    explicit PlaylistSongEditScreen(QWidget *parent = nullptr, QSqlDatabase* database = nullptr, bool isGuest = false, int userId = 0, int playlistId = 0, int songId = 0);
    ~PlaylistSongEditScreen();

signals:
    toPlaylistScreen(bool isGuest, int userId = 0, int playlistId = 0);

private:
    Ui::playlist_song_edit_screen *ui;
    QSqlDatabase* database;
    bool isGuest;
    int userId;
    int playlistId;
    int songId;

    void showPlaylist();

    SuggestionLineEdit* sle;
    QString fullFilePath;

    void setupUi();

    void handleFileDialog();
    void editSong();
    QStringList artistQuery(const QString& text);
};

#endif // PLAYLIST_SONG_EDIT_SCREEN_H
