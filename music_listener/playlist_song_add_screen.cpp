#include "playlist_song_add_screen.h"
#include "ui_playlist_song_add_screen.h"

#include <QGridLayout>
#include <QSqlQuery>
#include <Qmenu>

PlaylistSongAddScreen::PlaylistSongAddScreen(QWidget *parent, QSqlDatabase *database, bool isGuest, int userId, int playlistId) :
    QWidget(parent),
    ui(new Ui::playlist_song_add_screen)
    , database(database)
    , isGuest(isGuest)
    , userId(userId)
    , playlistId(playlistId)
    , nic(new NiceColumns(this))
{
    ui->setupUi(this);

    this->setLayout(ui->mainLayout);

    setupTopWidget();
    setupNiceColumns();

    connect(back_pb, &QPushButton::clicked, this, showPlaylistEdit);
}

PlaylistSongAddScreen::~PlaylistSongAddScreen()
{
    delete ui;
}

void PlaylistSongAddScreen::setupTopWidget()
{
    ui->top_w->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    QGridLayout* layout = new QGridLayout(ui->top_w);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    back_pb = new QPushButton(this);
    back_pb->setText("Back");
    layout->addWidget(back_pb, 0, 0, 1, 1, Qt::AlignRight | Qt::AlignHCenter);

    QLabel* playlist_l = new QLabel(this);
    playlist_l->setText("asddsa");
    layout->addWidget(playlist_l, 0, 0, 1, 1, Qt::AlignCenter);
}

void PlaylistSongAddScreen::setupNiceColumns()
{
    QVBoxLayout* layout = new QVBoxLayout(ui->niceColumns_w);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);

    layout->addWidget(nic);

    nic->addHeader("Title", Qt::AlignCenter);
    nic->addHeader("Author", Qt::AlignCenter);
    nic->addHeader("Visibility", Qt::AlignCenter);
    nic->addHeader("Filepath", Qt::AlignCenter);
    nic->addHeader("Date", Qt::AlignCenter);

    setupBody();

    nic->updateWidths();
    nic->checkScrollbars();
}

void PlaylistSongAddScreen::setupBody()
{
    QSqlQuery query;
/*
    query.prepare(
        "SELECT "
        "    songs.name, "
        "    authors.name, "
        "    songs.is_public, "
        "    songs.filename, "
        "    songs.created_at, "
        "    songs.id "
        "FROM songs "
        "LEFT JOIN playlist_contents "
        "    ON songs.id = playlist_contents.song "
        "JOIN authors "
        "    ON songs.author = authors.id "
        "WHERE playlist_contents.playlist IS NOT (?) "
        "    AND (songs.owner = (?) OR songs.is_public = 1)"
        );
    query.bindValue(0, playlistId);
    query.bindValue(1, userId);
//*/
    query.prepare(
        "SELECT "
        "    songs.name, "
        "    authors.name, "
        "    songs.is_public, "
        "    songs.filename, "
        "    songs.created_at, "
        "    songs.id, "
        "    SUM(playlist_contents.playlist = (?)) AS copies "
        "FROM songs "
        "LEFT JOIN playlist_contents "
        "    ON songs.id = playlist_contents.song "
        "JOIN authors "
        "    ON songs.author = authors.id "
        "WHERE songs.owner = (?) OR songs.is_public = 1 "
        "GROUP BY songs.id "
        "HAVING copies < 1 OR copies IS NULL"
        );
    query.bindValue(0, playlistId);
    query.bindValue(1, userId);
    if(!query.exec())
    {
        return;
    }
    int row = 0;
    while(query.next())
    {
        ElidedLabel* title = new ElidedLabel(this);
        title->setFullText(query.value(0).toString());
        nic->addBodyWidget(title, row, 0);

        ElidedLabel* author = new ElidedLabel(this);
        author->setFullText(query.value(1).toString());
        nic->addBodyWidget(author, row, 1);

        ElidedLabel* visibility = new ElidedLabel(this);
        if(query.value(2).toBool() == true)
        {
            visibility->setFullText("Public");
        }
        else
        {
            visibility->setFullText("Private");
        }
        nic->addBodyWidget(visibility, row, 2);

        ElidedLabel* filename = new ElidedLabel(this);
        filename->setFullText(query.value(3).toString());
        nic->addBodyWidget(filename, row, 3);

        ElidedLabel* date = new ElidedLabel(this);
        date->setFullText(query.value(4).toString());
        nic->addBodyWidget(date, row, 4);

        int index = query.value(5).toInt();

        QMenu* menu = new QMenu(this);

        QAction* addAction = menu->addAction("Add");
        connect(addAction, &QAction::triggered, this, [this, index](){
            //qDebug() << "adding song with id:" << index << "to playlist with id:" << playlistId;
            addSongQuery(index);
            nic->clearBody();
            setupBody();
        });

        nic->setRowMenu(row, menu);

        row++;
    }
}

void PlaylistSongAddScreen::addSongQuery(int songId)
{
    QSqlQuery query;
    query.prepare(
        "INSERT INTO playlist_contents "
        "(song, playlist, created_at) "
        "VALUES ((?), (?), datetime())"
        );
    query.bindValue(0, songId);
    query.bindValue(1, playlistId);

    if(!query.exec())
    {
        qDebug() << "database error";
    };

}

void PlaylistSongAddScreen::showPlaylistEdit()
{
    emit toPlaylistEditScreen(isGuest, userId, playlistId);
}
