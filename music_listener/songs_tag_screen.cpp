#include "songs_tag_screen.h"
#include "ui_songs_tag_screen.h"

#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QSqlQuery>
#include <QMenu>
#include <QMessageBox>

SongsTagScreen::SongsTagScreen(QWidget *parent, QSqlDatabase *database, bool isGuest, int userId, int songId) :
    QWidget(parent),
    ui(new Ui::SongsTagScreen)
    , database(database)
    , isGuest(isGuest)
    , userId(userId)
    , songId(songId)
    , nic(new NiceColumns(this))
{
    ui->setupUi(this);
    this->setLayout(ui->mainLayout);

    setupTopWidget();

    setupColumns();
}

SongsTagScreen::~SongsTagScreen()
{
    delete ui;
}

void SongsTagScreen::showSongs()
{
    emit updateSongId(0);
    emit toSongsScreen();
}

void SongsTagScreen::showAdd()
{
    emit toSongsTagAddScreen(isGuest, userId, songId);
}

void SongsTagScreen::setupTopWidget()
{
    QGridLayout* topLayout = new QGridLayout(ui->top_w);
    topLayout->setContentsMargins(0, 0, 0, 0);
    topLayout->setSpacing(0);

    QPushButton* add_pb = new QPushButton(this);
    add_pb->setText("Add");
    topLayout->addWidget(add_pb, 0, 0, 1, 1, Qt::AlignLeft);
    connect(add_pb, &QPushButton::clicked, this, showAdd);

    QString songName = "Song";
    QSqlQuery query;
    query.prepare(
        "SELECT name FROM songs WHERE id = (?)"
        );
    query.bindValue(0, songId);
    if(!query.exec())
    {
        return;
    }
    if(!query.next())
    {
        return;
    }
    songName = query.value(0).toString();

    QLabel* song_l = new QLabel(this);
    song_l->setText(songName);
    topLayout->addWidget(song_l, 0, 0, 1, 1, Qt::AlignCenter);

    QPushButton* back_pb = new QPushButton(this);
    back_pb->setText("Back");
    topLayout->addWidget(back_pb, 0, 0, 1, 1, Qt::AlignRight);
    connect(back_pb, &QPushButton::clicked, this, showSongs);

    ui->top_w->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
}

void SongsTagScreen::setupBody()
{
    QSqlQuery query;
    query.prepare(
        "SELECT "
        "   tags.name, "
        "   tags.id "
        "FROM songs "
        "JOIN song_tags "
        "   ON songs.id = song_tags.song "
        "JOIN tags "
        "   ON song_tags.tag = tags.id "
        "WHERE songs.id = (?)"
        );
    query.bindValue(0, songId);

    if(!query.exec())
    {
        qDebug() << "Database error";
        return;
    }

    int row = 0;
    while(query.next())
    {
        QString tagName = query.value(0).toString();
        int tagId = query.value(1).toInt();
        qDebug() << tagName;

        ElidedLabel* el = new ElidedLabel(this);
        el->setFullText(tagName);

        nic->addBodyWidget(el, row, 0);

        QMenu* menu = new QMenu(this);
        QAction* editAction = menu->addAction("edit");
        connect(editAction, QAction::triggered, this, [this, tagId](){
            //qDebug() << "editing" << tagId;
            emit toSongsTagEditScreen(isGuest, userId, songId, tagId);
        });

        QAction* removeAction = menu->addAction("remove");
        connect(removeAction, &QAction::triggered, this, [this, tagName, tagId](){
            //qDebug() << "removing" << tagId;
            QString message = "Are you sure you want to delete: ";
            deletePopup(message + "\n" + tagName, tagId);
        });

        nic->setRowMenu(row, menu);


        row++;
    }


    nic->checkScrollbars();
}

void SongsTagScreen::setupColumns()
{
    QVBoxLayout* columnsLayout = new QVBoxLayout(ui->columns_w);
    columnsLayout->setContentsMargins(0, 0, 0, 0);
    columnsLayout->setSpacing(0);

    columnsLayout->addWidget(nic);

    nic->addHeader("Tags", Qt::AlignCenter);

    setupBody();
}

void SongsTagScreen::deletePopup(const QString &text, const int index)
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
            "DELETE FROM song_tags "
            "WHERE song = (?)"
            "   AND tag = (?)"
            );
        query.bindValue(0, songId);
        query.bindValue(1, index);
        if(!query.exec())
        {
            deletePopup("Database Error", 0);
            return;
        }
        nic->clearBody();
        setupBody();
    }
}
