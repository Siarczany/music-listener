#include "playlist_edit_screen.h"
#include "ui_playlist_edit_screen.h"

#include <QSqlQuery>
#include <QMenu>

PlaylistEditScreen::PlaylistEditScreen(QWidget *parent, QSqlDatabase *database, bool isGuest, int userId, int playlistId) :
    QWidget(parent),
    ui(new Ui::Playlist_Edit_Screen)
    , database(database)
    , isGuest(isGuest)
    , userId(userId)
    , playlistId(playlistId)
{
    ui->setupUi(this);

    this->setLayout(ui->mainLayout);

    setupTopWidget();
    setupMiddleWidget();
    setupColumns();

    connect(back_pb, &QPushButton::clicked, this, showPlaylists);
    connect(add_pb, &QPushButton::clicked, this, showPlaylistsSongAdd);
}

PlaylistEditScreen::~PlaylistEditScreen()
{
    delete ui;
}

void PlaylistEditScreen::setupTopWidget()
{
    QGridLayout* topLayout = new QGridLayout(ui->top_w);
    topLayout->setSpacing(0);
    topLayout->setContentsMargins(0, 0, 0, 0);

    name_l = new QLabel(this);
    name_l->setText("Name");
    topLayout->addWidget(name_l, 0, 0, 1, 1, Qt::AlignVCenter | Qt::AlignLeft);

    back_pb = new QPushButton(this);
    back_pb->setText("Return");
    topLayout->addWidget(back_pb, 0, 0, 1, 1, Qt::AlignVCenter | Qt::AlignRight);

    nameQuery();
}

void PlaylistEditScreen::nameQuery()
{
    QSqlQuery query;
    query.prepare(
        "SELECT name FROM playlists WHERE id = (?)"
        );
    query.bindValue(0, playlistId);

    if(!query.exec())
    {
        return;
    }
    if(query.next())
    {
        ui->name_le->setText(query.value(0).toString());
    }
}

void PlaylistEditScreen::setupMiddleWidget()
{
    QGridLayout* middleLayout = new QGridLayout(ui->middle_w);
    middleLayout->setSpacing(0);
    middleLayout->setContentsMargins(0, 0, 0, 0);

    songs_l = new QLabel(this);
    songs_l->setText("Songs");
    middleLayout->addWidget(songs_l, 0, 0, 1, 1, Qt::AlignVCenter | Qt::AlignLeft);

    add_pb = new QPushButton(this);
    add_pb->setText("Add");
    middleLayout->addWidget(add_pb, 0, 0, 1, 1, Qt::AlignVCenter | Qt::AlignRight);
}

void PlaylistEditScreen::setupColumns()
{
    nic = new NiceColumns(this);
    nic->setAutoResizable(false);
    nic->addHeader("Title", Qt::AlignCenter);
    nic->addHeader("Author", Qt::AlignCenter);
    nic->addHeader("Visibility", Qt::AlignCenter);
    nic->addHeader("Filepath", Qt::AlignCenter);
    nic->addHeader("Added Date", Qt::AlignCenter);

    setupBody();

    QVBoxLayout* songsLayout = new QVBoxLayout(ui->songs_w);
    songsLayout->setSpacing(0);
    songsLayout->setContentsMargins(0, 0, 0, 0);

    songsLayout->addWidget(nic);
}

void PlaylistEditScreen::setupBody()
{
    QSqlQuery query;
    query.prepare(
        "SELECT "
        "    songs.name, "
        "    authors.name, "
        "    songs.is_public, "
        "    songs.filename, "
        "    playlist_contents.created_at, "
        "    songs.id, "
        "    playlist_contents.id "
        "FROM songs "
        "JOIN playlist_contents "
        "    ON songs.id = playlist_contents.song "
        "JOIN playlists "
        "    ON playlist_contents.playlist = playlists.id "
        "JOIN authors "
        "    ON songs.author = authors.id "
        "WHERE playlists.id = (?)"
        );
    query.bindValue(0, playlistId);

    if(!query.exec())
    {
        qDebug() << "niedobrze";
        return;
    }

    int row = 0;
    while(query.next())
    {
        ElidedLabel* name = new ElidedLabel(this);
        name->setFullText(query.value(0).toString());
        nic->addBodyWidget(name, row, 0);

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

        ElidedLabel* filepath = new ElidedLabel(this);
        filepath->setFullText(query.value(3).toString());
        nic->addBodyWidget(filepath, row, 3);

        ElidedLabel* addedDate = new ElidedLabel(this);
        addedDate->setFullText(query.value(4).toString());
        nic->addBodyWidget(addedDate, row, 4);

        int songIndex = query.value(5).toInt();
        int playlistContentIndex = query.value(6).toInt();

        QMenu* menu = new QMenu(this);

        QAction* editAction = menu->addAction("Edit");
        connect(editAction, &QAction::triggered, this, [this, songIndex](){
            //emit toPlaylistSongEdit
            //qDebug() << "editing song with id:" << songIndex;
            emit toPlaylistsSongEditScreen(isGuest, userId, playlistId, songIndex);
        });

        QAction* removeAction = menu->addAction("Remove");
        connect(removeAction, &QAction::triggered, this, [this, playlistContentIndex](){
            //remove this from playlist
            qDebug() << "removing playlist content with id:" << playlistContentIndex;
            removeSong(playlistContentIndex);

            nic->clearBody();

            setupBody();
        });

        nic->setRowMenu(row, menu);

        row++;
    }

    nic->updateWidths();
    nic->checkScrollbars();
}

void PlaylistEditScreen::removeSong(int index)
{
    QSqlQuery query;
    query.prepare(
        "DELETE FROM playlist_contents "
        "WHERE id = (?)"
        );
    query.bindValue(0, index);

    if(!query.exec())
    {
        qDebug() << "nima :(";
    }
}

void PlaylistEditScreen::showPlaylists()
{
    emit toPlaylistsScreen(isGuest, userId);
}

void PlaylistEditScreen::showPlaylistsSongAdd()
{
    emit toPlaylistsSongAddScreen(isGuest, userId, playlistId);
}
