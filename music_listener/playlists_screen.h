#ifndef PLAYLISTS_SCREEN_H
#define PLAYLISTS_SCREEN_H

#include <QWidget>
#include <QtSql>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <playlists_screen_slider.h>

namespace Ui {
class playlists_screen;
}

class playlists_screen : public QWidget
{
    Q_OBJECT

public:
    explicit playlists_screen(QWidget *parent = nullptr, QSqlDatabase* database = nullptr, bool is_guest = false, int user_id = 0);
    ~playlists_screen();

signals:
    to_login_screen();
    to_songs_screen();
    toPlaylistAddScreen(bool isGuest, int userId = 0);
    toPlayerScreen(bool isGuest, int userId = 0, int playlistId = 0);
    toPlaylistEditScreen(bool isGuest, int userId = 0, int playlistId = 0);

    updateIsGuest(bool isGuest);
    updateUserId(int userId);


private:
    Ui::playlists_screen *ui;
    QSqlDatabase* db;

    bool is_guest = false;
    int user_id;

    QLabel* username_l;
    QPushButton* log_out_pb;
    QPushButton* settings_pb;

    QLabel* tags_list_l;
    QScrollArea* tags_list_sa;
    QVBoxLayout* tags_layout;
    QScrollArea* playlists_sa;
    QVBoxLayout* playlists_layout;
    QWidget* padding_center;
    QWidget* padding_center_left;
    QWidget* padding_center_right;
    sliding_widget* resizer;
    QGridLayout* lists_layout;


    void setup_account_widget();

    void display_tags();
    void display_playlists();
    void setup_lists_widget();
    void show_tags_list(bool visibility);
    int tags_column_stretch = 1;

    void log_out();
    void show_songs();
    void showPlaylistAdd();

    void set_username();

    void fun_test();

    void clearLayout(QLayout* layout);
    void deletePlaylistPopup(const QString& text, const int index);
};

#endif // PLAYLISTS_SCREEN_H
