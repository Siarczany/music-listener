#ifndef SONGS_SCREEN_H
#define SONGS_SCREEN_H

#include <QWidget>
#include <QSqlDatabase>
#include "widgets/NiceColumns/nicecolumns.h"

namespace Ui {
class songs_screen;
}

class songs_screen : public QWidget
{
    Q_OBJECT

public:
    explicit songs_screen(QWidget *parent = nullptr, QSqlDatabase* database = nullptr, bool is_guest = false, int user_id = 0);
    ~songs_screen();

signals:
    to_playlists_screen(bool is_guest, int user_id = 0);
    toSongsAddScreen(bool isGuest, int userId = 0);
    toSongsEditScreen(bool isGuest, int userId = 0, int songId = 0);
    toSongsTagScreen(bool isGuest, int userId = 0, int songId = 0);

private:
    Ui::songs_screen *ui;
    QSqlDatabase* db;

    bool is_guest = false;
    int user_id;

    NiceColumns* nic;

    void show_playlists();
    void showSongsAdd();

    void setup_widget();
    void setupBody();
    void setupDisplay();

    void deletePopup(const QString& text, const int index);
};

#endif // SONGS_SCREEN_H
