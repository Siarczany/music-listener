#include "songs_edit_screen.h"
#include "ui_songs_edit_screen.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QVBoxLayout>
#include <QFileInfo>
#include <QFileDialog>
#include <texts.h>
#include <sizes.h>

SongsEditScreen::SongsEditScreen(QWidget *parent, QSqlDatabase *database, bool isGuest, int userId, int songId) :
    QWidget(parent),
    ui(new Ui::songs_edit_screen)
    , db(database)
    , userId(userId)
    , sle(new SuggestionLineEdit(this))
{
    this->isGuest = isGuest;
    this->songId = songId;
    ui->setupUi(this);

    ui->title_l->setToolTip(text::songTitle);
    ui->title_le->setToolTip(text::songTitle);
    ui->author_l->setToolTip(text::songAuthor);
    sle->setToolTip(text::songAuthor);
    ui->filename_l->setToolTip(text::songFilenameLabel);
    ui->filename_le->setToolTip(text::songFilenameLineEdit);
    ui->filename_pb->setToolTip(text::songFilenameButton);
    ui->seeableness_l->setToolTip(text::songSeeableness);
    ui->public_rb->setToolTip(text::songPublic);
    ui->private_rb->setToolTip(text::songPrivate);
    ui->edit_pb->setToolTip(text::songEdit);
    ui->cancel_pb->setToolTip(text::songReturn);

    ui->mainLayout->setAlignment(ui->title_l, Qt::AlignHCenter);
    ui->mainLayout->setAlignment(ui->title_le, Qt::AlignHCenter);
    ui->mainLayout->setAlignment(ui->author_l, Qt::AlignHCenter);
    ui->mainLayout->setAlignment(ui->author_sle, Qt::AlignHCenter);
    ui->filenameLayout->setAlignment(ui->filename_l, Qt::AlignLeft);
    ui->filenameLayout->setAlignment(ui->filename_pb, Qt::AlignRight);
    ui->mainLayout->setAlignment(ui->filename_le, Qt::AlignHCenter);
    ui->mainLayout->setAlignment(ui->seeableness_l, Qt::AlignHCenter);
    ui->seeablenessLayout->setAlignment(ui->private_rb, Qt::AlignLeft);
    ui->seeablenessLayout->setAlignment(ui->public_rb, Qt::AlignRight);
    ui->mainLayout->setAlignment(ui->edit_pb, Qt::AlignHCenter);
    ui->mainLayout->setAlignment(ui->userOutput_l, Qt::AlignHCenter);
    ui->mainLayout->setAlignment(ui->cancel_pb, Qt::AlignHCenter);

    ui->title_le->setMinimumWidth(size::ok_form_width);
    sle->setMinimumWidth(size::ok_form_width);
    ui->filename_le->setMinimumWidth(size::ok_form_width);
    ui->edit_pb->setMinimumWidth(size::ok_form_width);
    ui->cancel_pb->setMinimumWidth(size::ok_form_width);

    QVBoxLayout* sleLayout = new QVBoxLayout(ui->author_sle);
    sleLayout->setContentsMargins(0, 0, 0, 0);

    sleLayout->addWidget(sle);

    setupUi();

    connect(ui->cancel_pb, &QPushButton::clicked, this, showSongs);

    connect(ui->filename_pb, &QPushButton::clicked, this, handleFileDialog);

    connect(ui->edit_pb, &QPushButton::clicked, this, editSong);

    QWidget* mainConteiner = new QWidget(this);
    mainConteiner->setLayout(ui->mainLayout);

    QVBoxLayout* screenLayout = new QVBoxLayout(this);
    screenLayout->addWidget(mainConteiner, 0, Qt::AlignCenter);
}

SongsEditScreen::~SongsEditScreen()
{
    delete ui;
}

void SongsEditScreen::showSongs()
{
    emit toSongsScreen(isGuest, userId);
}

void SongsEditScreen::setupUi()
{
    QSqlQuery query;
    query.prepare(
        "SELECT "
        "   songs.name, "
        "   authors.name, "
        "   songs.filename, "
        "   songs.is_public "
        "FROM songs "
        "    JOIN authors "
        "        ON songs.author = authors.id "
        "    WHERE songs.id = (?)"
        );
    query.bindValue(0, songId);

    if(!query.exec())
    {
        qDebug() << "database error:" << db->lastError().text();
    }
    if(query.next())
    {
        QString title = query.value(0).toString();
        QString author = query.value(1).toString();
        fullFilePath = query.value(2).toString();
        bool isPublic = query.value(3).toBool();

        ui->title_le->setText(title);
        sle->setText(author);
        sle->setQuery([this](const QString& text){
            return artistQuery(text);
        });

        QFileInfo filename(fullFilePath);
        ui->filename_le->setText(filename.fileName());

        ui->public_rb->setChecked(isPublic);
        ui->private_rb->setChecked(!isPublic);

        if(isGuest)
        {
            ui->seeableness_l->hide();
            ui->public_rb->hide();
            ui->private_rb->hide();
        }
    }
}

void SongsEditScreen::handleFileDialog()
{
    QFileInfo filePath(fullFilePath);
    fullFilePath = QFileDialog::getOpenFileName(this, tr("Open file"), filePath.absolutePath(), tr("Audio Files (*.mp3 *.wav);;All Files (*)"));
    QFileInfo fileName(fullFilePath);
    ui->filename_le->setText(fileName.fileName());
}

void SongsEditScreen::editSong()
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
        "UPDATE songs SET "
        "name = (?), "
        "filename = (?), "
        "author = (?), "
        "is_public = (?) "
        "WHERE id = (?) "
        );
    query.bindValue(0, ui->title_le->text());
    query.bindValue(1, fullFilePath);
    query.bindValue(2, artistId);
    query.bindValue(3, ui->public_rb->isChecked());
    query.bindValue(4, songId);

    if(!query.exec())
    {
        ui->userOutput_l->setText("Database Error");
        db->rollback();
        return;
    }

    ui->userOutput_l->setText("Song Edited");
    db->commit();
}

QStringList SongsEditScreen::artistQuery(const QString &text)
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
