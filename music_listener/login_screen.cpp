#include "login_screen.h"
#include "ui_login_screen.h"

#include <QtSql>
#include <sizes.h>
#include <texts.h>

login_screen::login_screen(QWidget *parent, QSqlDatabase* database) :
    QWidget(parent),
    ui(new Ui::login_screen)
{
    db = database;
    ui->setupUi(this);

    QString guest_message = "Don't have an account yet?\nLog in as a guest and view public songs and playlists!";
    QString login_button_message = "Log in into your account.";
    QString register_message = "Don't have an account yet?\n"
                               "Create it here!";

    ui->login_l->setToolTip(text::login_tool_tip);
    ui->login_le->setToolTip(text::login_tool_tip);
    ui->password_l->setToolTip(text::password_tool_tip);
    ui->password_le->setToolTip(text::password_tool_tip);
    ui->guest_pb->setToolTip(guest_message);
    ui->create_pb->setToolTip(register_message);
    ui->login_pb->setToolTip(login_button_message);

    ui->login_le->setMinimumWidth(size::ok_form_width);
    ui->password_le->setMinimumWidth(size::ok_form_width);
    ui->login_pb->setMinimumWidth(size::ok_form_width);

    connect(ui->create_pb, &QPushButton::clicked, this, to_register_screen);
    connect(ui->login_pb, &QPushButton::clicked, this, &login_user);
    connect(ui->guest_pb, &QPushButton::clicked, [this](){
        emit to_playlists_screen(true);
    });

    ui->login_input_layout->setAlignment(ui->login_l, Qt::AlignHCenter);
    ui->login_input_layout->setAlignment(ui->login_le, Qt::AlignHCenter);

    ui->password_input_layout->setAlignment(ui->password_l, Qt::AlignHCenter);
    ui->password_input_layout->setAlignment(ui->password_le, Qt::AlignHCenter);

    ui->main_layout->setAlignment(ui->create_pb, Qt::AlignHCenter);

    //this->setLayout(ui->main_layout);

    QWidget* main_container = new QWidget(this);
    main_container->setLayout(ui->main_layout);

    QVBoxLayout* screen_layout = new QVBoxLayout(this);
    screen_layout->addWidget(main_container);
    screen_layout->setAlignment(main_container, Qt::AlignCenter);
}

login_screen::~login_screen()
{
    delete ui;
}

bool login_screen::check_login_les()
{
    if(ui->login_le->text().isEmpty())
    {
        ui->user_output_l->setText("Login must not be empty");
        return false;
    }
    if(ui->password_le->text().isEmpty())
    {
        ui->user_output_l->setText("Password must not be empty");
        return false;
    }
    return true;
}

void login_screen::login_user()
{
    QSqlQuery query;
    query.prepare("SELECT id FROM users WHERE login = (?) AND password = (?)");
    query.bindValue(0, ui->login_le->text());
    query.bindValue(1, ui->password_le->text());
    if(!query.exec())
    {
        ui->user_output_l->setText("Database error: " + db->lastError().text());
        return;
    }
    if(!query.next())
    {
        ui->user_output_l->setText("Incorrect Credentials");
        return;
    }
    //qDebug() << query.value(0).toInt();
    emit to_playlists_screen(false, query.value(0).toInt());
}
