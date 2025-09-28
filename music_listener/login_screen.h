#ifndef LOGIN_SCREEN_H
#define LOGIN_SCREEN_H

#include <QWidget>
#include <QSqlDatabase>

namespace Ui {
class login_screen;
}

class login_screen : public QWidget
{
    Q_OBJECT

public:
    explicit login_screen(QWidget *parent = nullptr, QSqlDatabase* database = nullptr);
    ~login_screen();

signals:
    to_register_screen();
    to_playlists_screen();

    updateIsGuest(bool isGuest);
    updateUserId(int userId);

private:
    Ui::login_screen *ui;
    QSqlDatabase* db;

    bool check_login_les();
    bool are_credentials_ok();
    void login_user();
};

#endif // LOGIN_SCREEN_H
