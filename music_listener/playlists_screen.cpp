#include "playlists_screen.h"
#include "ui_playlists_screen.h"

#include <QStackedLayout>
#include <QScrollArea>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QSettings>
#include <playlists_screen_slider.h>
#include "widgets/triplecheckbox.h"
#include "widgets/playlistlabel.h"
#include <QMenu>
#include <QMessageBox>

playlists_screen::playlists_screen(QWidget *parent, QSqlDatabase* database, bool is_guest, int user_id) :
    QWidget(parent),
    ui(new Ui::playlists_screen)
{
    db = database;
    this->is_guest = is_guest;
    this->user_id = user_id;
    ui->setupUi(this);

    this->setLayout(ui->main_layout);

    setup_account_widget(); // also możesz wejść do tej funkcji i pozmieniać nazwy layoutów na layout po prostu czy coś takiego
                            // no bo jak w funkcji to może tak być xd

    setup_lists_widget();   // perhaps to co wyżej w komentarzu xd

    set_username();

    connect(log_out_pb, QPushButton::clicked, this, &log_out);
    connect(ui->songs_pb, QPushButton::clicked, this, &show_songs);
    connect(ui->new_playlist_pb, &QPushButton::clicked, this, &showPlaylistAdd);
}

playlists_screen::~playlists_screen()
{
    delete ui;
}

void playlists_screen::setup_account_widget()
{
    QGridLayout* account_layout = new QGridLayout(ui->account_w);
    account_layout->setContentsMargins(0, 0, 0, 0);
    account_layout->setSpacing(0);

    username_l = new QLabel("username", this);
    username_l->setAlignment(Qt::AlignCenter);
    account_layout->addWidget(username_l, 0, 0, 1, 3, Qt::AlignCenter);

    log_out_pb = new QPushButton("Log Out", this);
    log_out_pb->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    //account_layout->addWidget(log_out_pb, 0, 2, 1, 1, Qt::AlignRight);

    settings_pb = new QPushButton("Settings", this);
    settings_pb->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QHBoxLayout* account_buttons_layout = new QHBoxLayout;
    account_buttons_layout->setContentsMargins(0, 0, 0, 0);
    account_buttons_layout->addWidget(settings_pb);
    account_buttons_layout->addWidget(log_out_pb);

    QWidget* account_buttons = new QWidget(this);
    account_buttons->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    account_buttons->setLayout(account_buttons_layout);
    account_layout->addWidget(account_buttons, 0, 2, 1, 1, Qt::AlignRight);
}

void playlists_screen::display_tags()
{
    QSqlQuery query;
    query.prepare(
        "SELECT name FROM tags"
        );
    if(!query.exec())
    {
        return;
    }

    while(query.next())
    {
        TripleCheckBox* tcb = new TripleCheckBox(this);
        tcb->setText(query.value(0).toString());
        tags_layout->addWidget(tcb);
        //tags_layout->addLayout(layout);
    }

    QWidget* wid = new QWidget(this);
    tags_layout->addWidget(wid, 1);
}

void playlists_screen::display_playlists()
{
    QSqlQuery query;
    query.prepare(
        "SELECT name, id FROM playlists"
        );
    if(!query.exec())
    {
        return;
    }

    while(query.next())
    {
        PlaylistLabel* pl = new PlaylistLabel(this);
        QString name = query.value(0).toString();
        pl->setText(name);

        int index = query.value(1).toInt();

        QMenu* menu = new QMenu(this);

        QAction* playAction = menu->addAction("Listen");
        connect(playAction, &QAction::triggered, this, [this, index](){
            //qDebug() << "listening to index:" << index;
            emit toPlayerScreen(is_guest, user_id, index);
        });

        QAction* editAction = menu->addAction("Edit");
        connect(editAction, &QAction::triggered, this, [this, index](){
            //qDebug() << "editing index:" << index;
            emit toPlaylistEditScreen(is_guest, user_id, index);
        });

        QAction* removeAction = menu->addAction("Remove");
        connect(removeAction, &QAction::triggered, this, [this, name, index](){
            //qDebug() << "removing:" << index;
            QString message = "Are you sure you want to delete: ";
            deletePlaylistPopup(message + "\n" + name, index);
        });

        pl->setMenu(menu);

        connect(pl, &PlaylistLabel::pressed, this, [this, index](){
            emit toPlayerScreen(is_guest, user_id, index);
        });

        playlists_layout->addWidget(pl);
    }

    QWidget* wid = new QWidget(this);
    playlists_layout->addWidget(wid, 1);
}

void playlists_screen::setup_lists_widget()
{
    lists_layout = new QGridLayout;
    lists_layout->setContentsMargins(0, 0, 0, 0);
    lists_layout->setSpacing(0);
    ui->lists_w->setLayout(lists_layout);

    // button icon tutorial xd
    //btn->setFlat(true);
    //QPixmap buttonImage("C:\\Users\\Administrator\\Desktop\\Untitled1.png");
    //QIcon buttonIcon(buttonImage);
    //btn->setIcon(buttonIcon);
    //btn->setStyleSheet("background-color: rgba(255, 255, 255, 0); ");
    QPushButton* show_tags_pb = new QPushButton("Select Tags", this);
    QPushButton* hide_tags_pb = new QPushButton("Hide Tags", this);
    QStackedLayout* tags_buttons_layout = new QStackedLayout;
    tags_buttons_layout->addWidget(show_tags_pb);
    tags_buttons_layout->addWidget(hide_tags_pb);
    tags_buttons_layout->setCurrentWidget(show_tags_pb);
    QWidget* tags_buttons_wrapper = new QWidget(this);
    tags_buttons_wrapper->setLayout(tags_buttons_layout);
    tags_buttons_wrapper->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    connect(show_tags_pb, QPushButton::clicked, this, [this, tags_buttons_layout, hide_tags_pb](){
        tags_buttons_layout->setCurrentWidget(hide_tags_pb);
        show_tags_list(true);
    });
    connect(hide_tags_pb, QPushButton::clicked, this, [this, tags_buttons_layout, show_tags_pb](){
        tags_buttons_layout->setCurrentWidget(show_tags_pb);
        show_tags_list(false);
    });

    tags_list_l = new QLabel("Tags", this);
    tags_list_l->setAlignment(Qt::AlignCenter);


    QLabel* playlists_l = new QLabel("Playlists", this);
    playlists_l->setAlignment(Qt::AlignCenter);


    tags_list_sa = new QScrollArea(this);
    tags_list_sa->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    tags_list_sa->setMinimumWidth(1);
    tags_list_sa->setWidgetResizable(true);

    QWidget* tags_content = new QWidget(this);
    tags_list_sa->setWidget(tags_content);
    tags_layout = new QVBoxLayout();
    //tags_layout->setContentsMargins(0, 0, 0, 0);
    tags_layout->setSpacing(0);

    tags_content->setLayout(tags_layout);

    display_tags();


    playlists_sa = new QScrollArea(this);
    playlists_sa->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    playlists_sa->setMinimumWidth(1);
    playlists_sa->setWidgetResizable(true);

    QWidget* playlists_contents = new QWidget(this);
    playlists_sa->setWidget(playlists_contents);
    playlists_layout = new QVBoxLayout();
    playlists_contents->setLayout(playlists_layout);

    display_playlists();


    QWidget* padding_left = new QWidget(this);
    padding_left->setMinimumWidth(1);
    QWidget* padding_right = new QWidget(this);
    padding_right->setMinimumWidth(1);

    resizer = new sliding_widget(this, lists_layout, tags_list_sa, playlists_sa);
    resizer->setFixedWidth(33);
    resizer->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Ignored);

    padding_center = new QWidget(this);
    padding_center->setFixedWidth(1);
    padding_center_left = new QWidget(this);
    padding_center_left->setFixedWidth((resizer->width()-padding_center->width())/2);
    padding_center_right = new QWidget(this);
    padding_center_right->setFixedWidth((resizer->width()-padding_center->width())/2);

    // padding list_1 list_1_center separator list_2_center list_2 padding
    // 0       1      2             3         4             5      6

    lists_layout->addWidget(padding_left, 0, 0, 1, 1);
    lists_layout->addWidget(padding_center, 3, 3, 1, 1);
    lists_layout->addWidget(padding_right, 6, 6, 1, 1);
    lists_layout->addWidget(padding_center_left, 2, 2, 1, 1);
    lists_layout->addWidget(padding_center_right, 4, 4, 1, 1);
    lists_layout->addWidget(tags_list_l, 1, 1, 1, 2, Qt::AlignCenter);
    lists_layout->addWidget(playlists_l, 1, 4, 1, 2, Qt::AlignCenter);
    lists_layout->addWidget(tags_list_sa, 3, 1, 1, 2);
    lists_layout->addWidget(playlists_sa, 3, 4, 1, 2);
    lists_layout->addWidget(tags_buttons_wrapper, 1, 0, 1, 7, Qt::AlignHCenter | Qt::AlignLeft);
    lists_layout->addWidget(resizer, 3, 2, 1, 3, Qt::AlignHCenter);

    lists_layout->setColumnStretch(0, 0);
    lists_layout->setColumnStretch(1, 1);
    lists_layout->setColumnStretch(2, 0);
    lists_layout->setColumnStretch(3, 0);
    lists_layout->setColumnStretch(4, 0);
    lists_layout->setColumnStretch(5, 3);
    lists_layout->setColumnStretch(6, 0);

    show_tags_list(false);
}

void playlists_screen::fun_test()
{
    tags_list_l->setVisible(false);
    tags_list_sa->setVisible(false);
    padding_center->setVisible(false);
    resizer->setVisible(false);
    lists_layout->setColumnStretch(1, 0);
    lists_layout->setColumnStretch(2, 0);
}

void playlists_screen::clearLayout(QLayout *layout)
{
    if (!layout) return;

    while (QLayoutItem* item = layout->takeAt(0)) {
        if (QWidget* widget = item->widget()) {
            widget->deleteLater();  // Schedules deletion
        }
        if (QLayout* childLayout = item->layout()) {
            clearLayout(childLayout);
        }
        delete item;
    }
}

void playlists_screen::deletePlaylistPopup(const QString &text, const int index)
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation of deletion",
                                  text,
                                  QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
        if(index == 0)
        {
            return;
        }
        QSqlQuery query;
        query.prepare(
            "DELETE FROM playlists "
            "WHERE id = (?)"
            );
        query.bindValue(0, index);
        if(!query.exec())
        {
            deletePlaylistPopup("Database Error", 0);
            return;
        }
        clearLayout(playlists_layout);
        display_playlists();
    }
}

void playlists_screen::show_tags_list(bool visibility)
{
    tags_list_l->setVisible(visibility);
    tags_list_sa->setVisible(visibility);
    padding_center_left->setVisible(visibility);
    padding_center->setVisible(visibility);
    padding_center_right->setVisible(visibility);
    resizer->setVisible(visibility);

    if(visibility == true)
    {
        lists_layout->setColumnStretch(1, tags_column_stretch);
    }
    else
    {
        tags_column_stretch = lists_layout->columnStretch(1);
        lists_layout->setColumnStretch(1, 0);
    }
}

void playlists_screen::log_out()
{
    QSettings settings("settings.ini", QSettings::IniFormat);
    settings.setValue("lastUser", "");
    emit to_login_screen();
}

void playlists_screen::show_songs()
{
    emit to_songs_screen(is_guest, user_id);
}

void playlists_screen::showPlaylistAdd()
{
    emit toPlaylistAddScreen(is_guest, user_id);
}

void playlists_screen::set_username()
{
    if(is_guest)
    {
        username_l->setText("Guest");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT name FROM users WHERE id = (?)");
    query.bindValue(0, user_id);
    if(!query.exec())
    {
        username_l->setText("user");
        return;
    }
    if(query.next())
    {
        QString username = query.value(0).toString();
        if(username.isEmpty())
        {
            username_l->setText("user");
        }
        else
        {
            username_l->setText(username);
        }
    }

}
