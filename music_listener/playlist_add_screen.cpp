#include "playlist_add_screen.h"
#include "ui_playlist_add_screen.h"

#include <QVBoxLayout>
#include "texts.h"
#include "sizes.h"
#include <QSqlQuery>

PlaylistAddScreen::PlaylistAddScreen(QWidget *parent, QSqlDatabase *db, bool isGuest, int userId) :
    QWidget(parent),
    ui(new Ui::playlist_add_screen)
    , database(db)
    , isGuest(isGuest)
    , userId(userId)
{
    ui->setupUi(this);

    ui->name_l->setToolTip(text::playlistName);
    ui->name_le->setToolTip(text::playlistName);

    ui->add_pb->setToolTip("Add playlist.");
    ui->back_pb->setToolTip("Return.");

    ui->mainLayout->setAlignment(ui->name_l, Qt::AlignHCenter);
    ui->mainLayout->setAlignment(ui->name_le, Qt::AlignHCenter);
    ui->mainLayout->setAlignment(ui->add_pb, Qt::AlignHCenter);
    ui->mainLayout->setAlignment(ui->userOutput_l, Qt::AlignHCenter);
    ui->mainLayout->setAlignment(ui->back_pb, Qt::AlignHCenter);

    ui->name_le->setMinimumWidth(size::ok_form_width);
    ui->add_pb->setMinimumWidth(size::ok_form_width);
    ui->back_pb->setMinimumWidth(size::ok_form_width);

    QWidget* container = new QWidget(this);
    container->setLayout(ui->mainLayout);

    QVBoxLayout* screenLayout = new QVBoxLayout(this);
    screenLayout->addWidget(container);
    screenLayout->setAlignment(container, Qt::AlignCenter);

    connect(ui->add_pb, &QPushButton::clicked, this, &addPlaylist);
    connect(ui->back_pb, &QPushButton::clicked, this, showPlaylistsScreen);
}

PlaylistAddScreen::~PlaylistAddScreen()
{
    delete ui;
}

void PlaylistAddScreen::addPlaylist()
{
    if(ui->name_le->text().isEmpty())
    {
        if(!emptyName)
        {
            ui->userOutput_l->setText("If you want an empty name press add again");
            emptyName = true;
            return;
        }
    }

    addQuery();
}

void PlaylistAddScreen::addQuery()
{
    QSqlQuery query;
    query.prepare(
        "INSERT INTO playlists "
        "(name, owner, created_at) "
        "VALUES ((?), (?), datetime())"
        );
    query.bindValue(0, ui->name_le->text());
    query.bindValue(1, userId);

    if(!query.exec())
    {
        ui->userOutput_l->setText("Database Error");
        qDebug() << "aaa";
        return;
    }

}

void PlaylistAddScreen::showPlaylistsScreen()
{
    emit toPlaylistsScreen(isGuest, userId);
}
