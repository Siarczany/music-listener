#include "register_screen.h"
#include "ui_register_screen.h"

#include <QSqlQuery>
#include <QtSql>
#include <texts.h>
#include <sizes.h>

register_screen::register_screen(QWidget *parent, QSqlDatabase* database) :
    QWidget(parent),
    ui(new Ui::register_screen)
{
    ui->setupUi(this);
    db = database;

    QString password_again_message = "Please input your password again to decrease the chances of making a typo.\n" + text::password_tool_tip_2;
    QString name_message = "Name displayed to you in the app.";

    ui->login_l->setToolTip(text::login_tool_tip);
    ui->login_le->setToolTip(text::login_tool_tip);
    ui->password_l->setToolTip(text::password_tool_tip);
    ui->password_le->setToolTip(text::password_tool_tip);
    ui->password_again_l->setToolTip(password_again_message);
    ui->password_again_le->setToolTip(password_again_message);
    ui->name_l->setToolTip(name_message);
    ui->name_le->setToolTip(name_message);

    ui->main_layout->setAlignment(ui->login_l, Qt::AlignHCenter);
    ui->main_layout->setAlignment(ui->login_le, Qt::AlignHCenter);
    ui->main_layout->setAlignment(ui->password_l, Qt::AlignHCenter);
    ui->main_layout->setAlignment(ui->password_le, Qt::AlignHCenter);
    ui->main_layout->setAlignment(ui->password_again_l, Qt::AlignHCenter);
    ui->main_layout->setAlignment(ui->password_again_le, Qt::AlignHCenter);
    ui->main_layout->setAlignment(ui->name_l, Qt::AlignHCenter);
    ui->main_layout->setAlignment(ui->name_le, Qt::AlignHCenter);
    ui->main_layout->setAlignment(ui->register_pb, Qt::AlignHCenter);
    ui->main_layout->setAlignment(ui->error_l, Qt::AlignHCenter);
    ui->main_layout->setAlignment(ui->back_pb, Qt::AlignHCenter);

    ui->login_le->setMinimumWidth(size::ok_form_width);
    ui->password_le->setMinimumWidth(size::ok_form_width);
    ui->password_again_le->setMinimumWidth(size::ok_form_width);
    ui->name_le->setMinimumWidth(size::ok_form_width);
    ui->register_pb->setMinimumWidth(size::ok_form_width);
    ui->back_pb->setMinimumWidth(size::ok_form_width);

    QFontMetrics fm(ui->error_l->font());
    int textWidth = fm.horizontalAdvance("If you are sure you don't want a username click Register again"); // longest string
    //qDebug() << textWidth;
    ui->error_l->setMinimumWidth(textWidth);

    connect(ui->register_pb, &QPushButton::clicked, this, &register_user);
    connect(ui->back_pb, &QPushButton::clicked, this, &to_login_screen);

    //this->setLayout(ui->verticalLayout);
    QWidget* main_container = new QWidget(this);
    main_container->setLayout(ui->main_layout);

    QVBoxLayout* screen_layout = new QVBoxLayout(this);
    screen_layout->addWidget(main_container);
    screen_layout->setAlignment(main_container, Qt::AlignCenter);
}

register_screen::~register_screen()
{
    delete ui;
}

bool register_screen::is_login_free()
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM users WHERE login = (?)");
    query.bindValue(0, ui->login_le->text());
    if(!query.exec())
    {
        ui->error_l->setText("Database Error: " + db->lastError().text());
        qDebug() << db->lastError().text();
        return false;
    }
    query.next();
    if(query.value(0) == 0)
    {
        return true;
    }
    else
    {
        ui->error_l->setText("This login has been taken");
        return false;
    }
}

bool register_screen::check_registration_les()
{
    if(ui->login_le->text().isEmpty())
    {
        ui->error_l->setText("Login must not be empty");
        empty_name_confirmation = false;
        return false;
    }
    if(ui->password_le->text().isEmpty())
    {
        ui->error_l->setText("Password must not be empty");
        empty_name_confirmation = false;
        return false;
    }
    if(ui->password_again_le->text() != ui->password_le->text())
    {
        ui->error_l->setText("Incorrect password");
        empty_name_confirmation = false;
        return false;
    }
    if(ui->name_le->text().isEmpty())
    {
        if(empty_name_confirmation == false)
        {
            ui->error_l->setText("If you are sure you don't want a username click Register again");
            ui->error_l->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
            empty_name_confirmation = true;
            return false;
        }
    }
    return true;
}

void register_screen::register_user()
{
    if(check_registration_les() == false)
    {
        return;
    }
    if(is_login_free() == false)
    {
        return;
    }
    QSqlQuery query;
    query.prepare("INSERT INTO users (login, password, name, created_at) VALUES (?, ?, ?, CURRENT_TIMESTAMP)");
    query.bindValue(0, ui->login_le->text());
    query.bindValue(1, ui->password_le->text());
    query.bindValue(2, ui->name_le->text());
    if(!query.exec())
    {
        ui->error_l->setText("Database error: " + db->lastError().text());
        qDebug() << db->lastError().text();
        return;
    }
    ui->error_l->setText("Account Created!");
}
