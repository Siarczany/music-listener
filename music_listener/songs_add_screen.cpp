#include "songs_add_screen.h"
#include "ui_songs_add_screen.h"

#include <QCompleter>
#include <QSqlQuery>
#include <QFileDialog>
#include "sizes.h"
#include "texts.h"

songs_add_screen::songs_add_screen(QWidget *parent, QSqlDatabase *database, bool isGuest, int userId) :
    QWidget(parent)
    , ui(new Ui::songs_add_screen)
    , db(database)
    , sle(new SuggestionLineEdit(this))
{
    this->isGuest = isGuest;
    this->userId = userId;

    ui->setupUi(this);

    ui->title_l->setToolTip(text::songTitle);
    ui->title_le->setToolTip(text::songTitle);
    ui->author_l->setToolTip(text::songAuthor);
    sle->setToolTip(text::songAuthor);
    ui->filename_l->setToolTip(text::songFilenameLabel);
    ui->filename_le->setToolTip(text::songFilenameLineEdit);
    ui->filename_pb->setToolTip(text::songFilenameButton);
    ui->seeableness_l->setToolTip(text::songSeeableness);
    if(isGuest)
    {
        ui->public_rb->setToolTip(text::songPublicGuest);
    }
    else
    {
        ui->public_rb->setToolTip(text::songPublic);
    }
    ui->private_rb->setToolTip(text::songPrivate);
    ui->add_pb->setToolTip("Add song and assign it to your artist.");
    ui->back_pb->setToolTip(text::songReturn);

    ui->mainLayout->setAlignment(ui->title_l, Qt::AlignHCenter);
    ui->mainLayout->setAlignment(ui->title_le, Qt::AlignHCenter);
    ui->mainLayout->setAlignment(ui->author_l, Qt::AlignHCenter);
    ui->mainLayout->setAlignment(ui->author_sle, Qt::AlignHCenter);
    ui->fileLayout->setAlignment(ui->filename_l, Qt::AlignLeft);
    ui->fileLayout->setAlignment(ui->filename_pb, Qt::AlignRight);
    ui->mainLayout->setAlignment(ui->filename_le, Qt::AlignHCenter);
    ui->mainLayout->setAlignment(ui->seeableness_l, Qt::AlignHCenter);
    if(isGuest)
    {
        ui->seeablenessLayout->setAlignment(ui->public_rb, Qt::AlignLeft);
    }
    else
    {
        ui->seeablenessLayout->setAlignment(ui->private_rb, Qt::AlignLeft);
        ui->seeablenessLayout->setAlignment(ui->public_rb, Qt::AlignRight);
    }
    ui->mainLayout->setAlignment(ui->add_pb, Qt::AlignHCenter);
    ui->mainLayout->setAlignment(ui->userOutput_l, Qt::AlignHCenter);
    ui->mainLayout->setAlignment(ui->back_pb, Qt::AlignHCenter);

    ui->title_le->setMinimumWidth(size::ok_form_width);
    sle->setMinimumWidth(size::ok_form_width);
    ui->filename_le->setMinimumWidth(size::ok_form_width);
    ui->add_pb->setMinimumWidth(size::ok_form_width);
    ui->back_pb->setMinimumWidth(size::ok_form_width);



    QVBoxLayout* sleLayout = new QVBoxLayout(ui->author_sle);
    sleLayout->setContentsMargins(0, 0, 0, 0);

    sleLayout->addWidget(sle);

    sle->setQuery([this](const QString& text) {
        //return this->artistsQuery(text);
        return artistQuery(text);
    });

    if(isGuest)
    {
        ui->public_rb->setChecked(true);
        ui->private_rb->hide();
    }
    else
    {
        ui->private_rb->setChecked(true);
    }

    connect(ui->filename_pb, &QPushButton::clicked, this, handleFileDialog);

    connect(ui->add_pb, &QPushButton::clicked, this, addSong);

    connect(ui->back_pb, &QPushButton::clicked, this, showSongs);


    QWidget* mainConteiner = new QWidget(this);
    mainConteiner->setLayout(ui->mainLayout);

    QVBoxLayout* screenLayout = new QVBoxLayout(this);
    screenLayout->addWidget(mainConteiner, 0, Qt::AlignCenter);
}

songs_add_screen::~songs_add_screen()
{
    delete ui;
}

void songs_add_screen::showSongs()
{
    emit toSongsScreen(isGuest, userId);
}

QStringList songs_add_screen::artistQuery(const QString &text)
{
    QStringList list;


    QSqlQuery query;
    //*
    query.prepare(
        "SELECT "
        "	authors.name AS artist, "
        "	COUNT(songs.name) AS amount "
        "FROM authors "
        "LEFT JOIN songs "
        "	ON authors.id = songs.author "
        "WHERE (authors.owner = (?) "
        "	OR authors.is_public = 1) "
        "   AND instr(authors.name, (?)) "
        "GROUP BY artist "
        "ORDER BY authors.is_public ASC, amount DESC "
        "LIMIT 10"
        );
    //*/
    query.bindValue(0, userId);
    query.bindValue(1, text);
    if(!query.exec())
    {
        return list;
    }
    while(query.next())
    {
        list << query.value(0).toString();
    }
    return list;
}

void songs_add_screen::handleFileDialog()
{
    fullFilePath = QFileDialog::getOpenFileName(this, tr("Open file"), fullFilePath, tr("Audio Files (*.mp3 *.wav);;All Files (*)"));
    QFileInfo fileName(fullFilePath);
    ui->filename_le->setText(fileName.fileName());
}

int songs_add_screen::artistId()
{
    QSqlQuery query;
    query.prepare(
        "SELECT id "
        "FROM authors "
        "WHERE owner = (?) "
        "   OR is_public = 1 "
        "   AND name = (?)"
        );
    query.bindValue(0, userId);
    query.bindValue(1, sle->text());
    if(!query.exec())
    {
        ui->userOutput_l->setText("Database error");
        return 0; // doesn't exists
    }
    if(query.next())
    {
        return query.value(0).toInt();
    }
    return 0; // doesn't exists
}

void songs_add_screen::addSong()
{
    if(ui->title_le->text().isEmpty())
    {
        ui->userOutput_l->setText("Title cannot be empty");
        return;
    }

    if(sle->text().isEmpty())
    {
        ui->userOutput_l->setText("Author cannot be empty");
        return;
    }

    if(fullFilePath.isEmpty())
    {
        ui->userOutput_l->setText("There must be a file selected");
        return;
    }

    db->transaction();

    int artistId = 0;

    QSqlQuery query;
    query.prepare(
        "SELECT id "
        "FROM authors "
        "WHERE (owner = (?) "
        "   OR is_public = 1) "
        "   AND name = (?)"
        );
    query.bindValue(0, userId);
    query.bindValue(1, sle->text());
    if(!query.exec())
    {
        ui->userOutput_l->setText("Database error");
        db->rollback();
        return;
    }
    if(query.next())
    {
        artistId = query.value(0).toInt();
    }
    else
    {
        query.prepare(
            "INSERT INTO authors "
            "(name, description, owner, is_public, created_at) "
            "VALUES ((?), (?), (?), (?), datetime())"
            );
        query.bindValue(0, sle->text());
        query.bindValue(1, "no description");
        query.bindValue(2, userId);
        query.bindValue(3, ui->public_rb->isChecked());

        if(!query.exec())
        {
            ui->userOutput_l->setText("Database error");
            db->rollback();
            return;
        }

        artistId = query.lastInsertId().toInt();
    }


    query.prepare(
        "INSERT INTO songs "
        "(name, filename, author, owner, is_public, created_at) "
        "VALUES (?, ?, ?, ?, ?, datetime())"
        );
    query.bindValue(0, ui->title_le->text());
    query.bindValue(1, fullFilePath);
    query.bindValue(2, artistId);
    query.bindValue(3, userId);
    query.bindValue(4, ui->public_rb->isChecked());

    if(!query.exec())
    {
        ui->userOutput_l->setText("Database error");
        db->rollback();
        return;
    }

    ui->userOutput_l->setText("Song Added");
    db->commit();
}
