#include "songs_tag_add_screen.h"
#include "ui_songs_tag_add_screen.h"


#include <QSqlQuery>

SongsTagAddScreen::SongsTagAddScreen(QWidget *parent, QSqlDatabase *database, bool isGuest, int userId, int songId) :
    QWidget(parent),
    ui(new Ui::songs_tag_add_screen)
    , database(database)
    , isGuest(isGuest)
    , userId(userId)
    , songId(songId)
    , sle(new SuggestionLineEdit(this))
{
    ui->setupUi(this);



    QVBoxLayout* screenLayout = new QVBoxLayout(this);
    screenLayout->setContentsMargins(0, 0, 0, 0);
    screenLayout->setSpacing(0);

    QWidget* container = new QWidget(this);
    container->setLayout(ui->mainLayout);
    screenLayout->addWidget(container, 0, Qt::AlignCenter);

    setupSLE();

    connect(ui->add_pb, &QPushButton::clicked, this, addTag);
    connect(ui->back_pb, &QPushButton::clicked, this, showSongsTags);
}

SongsTagAddScreen::~SongsTagAddScreen()
{
    delete ui;
}

void SongsTagAddScreen::showSongsTags()
{
    qDebug() << "here";
    emit toSongsTagsScreen(isGuest, userId, songId);
}

void SongsTagAddScreen::setupSLE()
{
    QVBoxLayout* nameLayout = new QVBoxLayout(ui->name_sle);
    nameLayout->addWidget(sle);

    sle->setQuery([this](const QString& text){
        return nameQuery(text);
    });








}

QStringList SongsTagAddScreen::nameQuery(const QString &text)
{
    QStringList list;

    QSqlQuery query;
    query.prepare(
        "SELECT name "
        "FROM tags "
        "    WHERE owner = (?) "
        "AND instr(name, (?)) "
        "LIMIT 10"
        );
    query.bindValue(0, userId);
    query.bindValue(1, text);
    if(!query.exec())
    {
        return list;
    }

    while(query.next())
    {
        list << query.value(0).toString();
        //qDebug() << query.value(0).toString();
    }
    return list;
}

int SongsTagAddScreen::tagId()
{
    QSqlQuery query;
    query.prepare(
        "SELECT id "
        "FROM tags "
        "   WHERE owner = (?) "
        "   AND instr(name, (?))"
        );
    query.bindValue(0, userId);
    query.bindValue(1, sle->text());

    if(!query.exec())
    {
        return 0;
    }
    if(!query.next())
    {
        return 0;
    }
    return query.value(0).toInt();
}

void SongsTagAddScreen::addTag()
{
    if(sle->text().isEmpty())
    {
        ui->userOutput_l->setText("Name cannot be empty");
        return;
    }

    database->transaction();

    int tagId = 0;

    QSqlQuery query;
    query.prepare(
        "SELECT id "
        "FROM tags "
        "   WHERE owner = (?) "
        "   AND instr(name, (?))"
        );
    query.bindValue(0, userId);
    query.bindValue(1, sle->text());

    if(!query.exec())
    {
        ui->userOutput_l->setText("Database error");
        database->rollback();
        return;
    }
    if(query.next())
    {
        tagId = query.value(0).toInt();
    }
    else
    {
        query.prepare(
            "INSERT INTO tags "
            "(name, owner, created_at) "
            "VALUES ((?), (?), datetime())"
            );
        query.bindValue(0, sle->text());
        query.bindValue(1, userId);

        if(!query.exec())
        {
            ui->userOutput_l->setText("Database error");
            database->rollback();
            return;
        }

        tagId = query.lastInsertId().toInt();
    }

    query.prepare(
        "INSERT INTO song_tags "
        "(song, tag, created_at) "
        "VALUES ((?), (?), datetime())"
        );
    query.bindValue(0, songId);
    query.bindValue(1, tagId);

    if(!query.exec())
    {
        ui->userOutput_l->setText("Database error");
        database->rollback();
        return;
    }

    ui->userOutput_l->setText("Tag Added");
    database->commit();

}
