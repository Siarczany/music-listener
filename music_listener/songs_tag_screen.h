#ifndef SONGS_TAG_SCREEN_H
#define SONGS_TAG_SCREEN_H

#include <QWidget>
#include <QSqlDatabase>
#include "widgets/NiceColumns/nicecolumns.h"

namespace Ui {
class SongsTagScreen;
}

class SongsTagScreen : public QWidget
{
    Q_OBJECT

public:
    explicit SongsTagScreen(QWidget *parent = nullptr, QSqlDatabase* database = nullptr, bool isGuest = false, int userId = 0, int songId = 0);
    ~SongsTagScreen();

signals:
    toSongsScreen();
    toSongsTagAddScreen(bool isGuest, int userId = 0, int songId = 0);
    toSongsTagEditScreen(bool isGuest, int userId = 0, int songId = 0, int tagId = 0);

    updateSongId(int songId);

private:
    Ui::SongsTagScreen *ui;
    QSqlDatabase* database;

    bool isGuest;
    int userId;
    int songId;

    NiceColumns* nic;

    void showSongs();
    void showAdd();

    void setupTopWidget();
    void setupBody();
    void setupColumns();

    void deletePopup(const QString& text, const int index);
};

#endif // SONGS_TAG_SCREEN_H
