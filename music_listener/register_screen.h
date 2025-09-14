#ifndef REGISTER_SCREEN_H
#define REGISTER_SCREEN_H

#include <QWidget>
#include <QSqlDatabase>

namespace Ui {
class register_screen;
}

class register_screen : public QWidget
{
    Q_OBJECT

public:
    explicit register_screen(QWidget *parent = nullptr, QSqlDatabase* database = nullptr);
    ~register_screen();

signals:
    to_login_screen();

private:
    Ui::register_screen *ui;
    QSqlDatabase* db;
    bool empty_name_confirmation = false;

    bool is_login_free();
    bool check_registration_les();
    void register_user();
};

#endif // REGISTER_SCREEN_H
