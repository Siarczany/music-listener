#include "songs_screen.h"
#include "ui_songs_screen.h"

#include <QSqlQuery>
#include <QVBoxLayout>
#include <QSqlError>
#include <QPushButton>
#include <QMessageBox>
#include <QMenu>

songs_screen::songs_screen(QWidget *parent, QSqlDatabase *database, bool is_guest, int user_id) :
    QWidget(parent),
    ui(new Ui::songs_screen)
    , nic(new NiceColumns(this))
{
    db = database;
    this->is_guest = is_guest;
    this->user_id = user_id;
    ui->setupUi(this);

    this->setLayout(ui->main_layout);

    setup_widget();

    setupDisplay();

    //setup_scroll_area();

}


songs_screen::~songs_screen()
{
    delete ui;
}

void songs_screen::show_playlists()
{
    emit to_playlists_screen();
}

void songs_screen::showSongsAdd()
{
    emit toSongsAddScreen();
}

void songs_screen::setup_widget()
{
    ui->top_w->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    QGridLayout* layout = new QGridLayout(ui->top_w);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    //ui->top_w->setLayout(layout);

    QPushButton* add_pb = new QPushButton("Add", this);
    layout->addWidget(add_pb, 0, 0, 1, 1, Qt::AlignHCenter | Qt::AlignLeft);
    connect(add_pb, &QPushButton::clicked, this, showSongsAdd);

    QLabel* screen_l = new QLabel("Songs", this);
    layout->addWidget(screen_l, 0, 0, 1, 1, Qt::AlignCenter);

    QPushButton* back_pb = new QPushButton("Back", this);
    layout->addWidget(back_pb, 0, 0, 1, 1, Qt::AlignHCenter | Qt::AlignRight);
    connect(back_pb, QPushButton::clicked, this, &show_playlists);
}

void songs_screen::setupBody()
{
    QSqlQuery query;
    query.prepare(
        "SELECT "
        "songs.name, "
        "authors.name, "
        "songs.filename, "
        "songs.is_public, "
        "songs.created_at, "
        "songs.id "
        "FROM songs "
        "JOIN authors "
        "ON songs.author = authors.id "
        "WHERE songs.owner = (?) OR songs.is_public = 1");
    query.bindValue(0, user_id);
    if(!query.exec())
    {
        qDebug() << db->lastError().text();
        return;
    }
    int row = 0;
    while(query.next())
    {
        ElidedLabel* songName = new ElidedLabel(this);
        QString name = query.value(0).toString();
        songName->setFullText(name);
        songName->setAlignment(Qt::AlignLeft);
        nic->addBodyWidget(songName, row, 0);

        ElidedLabel* authorName = new ElidedLabel(this);
        authorName->setFullText(query.value(1).toString());
        authorName->setAlignment(Qt::AlignLeft);
        nic->addBodyWidget(authorName, row, 1);

        ElidedLabel* filepath = new ElidedLabel(this);
        filepath->setFullText(query.value(2).toString());
        filepath->setAlignment(Qt::AlignRight);
        nic->addBodyWidget(filepath, row, 2);

        ElidedLabel* seeableness = new ElidedLabel(this);
        if(query.value(3).toBool() == true)
        {
            seeableness->setFullText("Public");
        }
        else
        {
            seeableness->setFullText("Private");
        }
        seeableness->setAlignment(Qt::AlignCenter);
        nic->addBodyWidget(seeableness, row, 3);

        ElidedLabel* creationTime = new ElidedLabel(this);
        creationTime->setFullText(query.value(4).toString());
        creationTime->setAlignment(Qt::AlignRight);
        nic->addBodyWidget(creationTime, row, 4);

        int index = query.value(5).toInt();

        QMenu* menu = new QMenu(this);

        QAction* tagAction = menu->addAction("Tag");
        connect(tagAction, &QAction::triggered, this, [this, index](){
            emit updateSongsId(index);
            emit toSongsTagScreen();
        });
        QAction* editAction = menu->addAction("Edit");
        connect(editAction, &QAction::triggered, this, [this, index](){
            emit updateSongsId(index);
            emit toSongsEditScreen();
        });
        nic->setRowMenu(row, menu);
        QAction* removeAction = menu->addAction("Delete");
        connect(removeAction, &QAction::triggered, this, [this, name, index](){
            QString message = "Are you sure you want to delete: ";
            deletePopup(message + "\n" + name, index);
        });
        nic->setRowMenu(row, menu);

        row++;
    }

    nic->updateWidths();
    nic->checkScrollbars();
}

void songs_screen::setupDisplay()
{
    //NiceColumns* nic = new NiceColumns(this);
    //ui->main_layout->addWidget(nic);

    QVBoxLayout* nicLayout = new QVBoxLayout(ui->niceColumns_w);
    nicLayout->setSpacing(0);
    nicLayout->setContentsMargins(0, 0, 0, 0);
    nicLayout->addWidget(nic);

/*
    connect(nic, &NiceColumns::tag, this, [this](int index){
        emit toSongsTagScreen(is_guest, user_id, index);
    });
    connect(nic, &NiceColumns::edit, this, [this](int index){
        //qDebug() << "edited" << index;
        emit toSongsEditScreen(is_guest, user_id, index);
        //nic->checkScrollbars();
    });
    connect(nic, &NiceColumns::remove, this, [this](int index){
        QSqlQuery query;
        query.prepare(
            "SELECT name "
            "FROM songs "
            "WHERE id = (?)"
            );
        query.bindValue(0, index);

        if(!query.exec())
        {
            deletePopup("Database Error", 0);
        }

        if(!query.next())
        {
            deletePopup("Database Error", 0);
        }
        QString title = query.value(0).toString();
        QString message = "Are you sure you want to delete: ";
        deletePopup(message + "\n" + title, index);
    });
//*/



    //nic->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    nic->setAutoResizable(true);
    nic->addHeader("Title", Qt::AlignCenter);
    nic->addHeader("Author", Qt::AlignCenter);
    nic->addHeader("Lokalizacja Pliku", Qt::AlignCenter);
    nic->addHeader("Dostępność", Qt::AlignCenter);
    nic->addHeader("Data Stworzenia", Qt::AlignCenter);

    setupBody();
/*
    QSqlQuery query;
    query.prepare(
        "SELECT "
            "songs.name, "
            "authors.name, "
            "songs.filename, "
            "songs.is_public, "
            "songs.created_at, "
            "songs.id "
        "FROM songs "
        "JOIN authors "
            "ON songs.author = authors.id "
        "WHERE songs.owner = (?) OR songs.is_public = 1");
    query.bindValue(0, user_id);
    if(!query.exec())
    {
        qDebug() << db->lastError().text();
        return;
    }
    int row = 0;
    while(query.next())
    {
        ElidedLabel* songName = new ElidedLabel(this);
        songName->setFullText(query.value(0).toString());
        songName->setAlignment(Qt::AlignLeft);
        nic->addBodyWidget(songName, row, 0);

        ElidedLabel* authorName = new ElidedLabel(this);
        authorName->setFullText(query.value(1).toString());
        authorName->setAlignment(Qt::AlignLeft);
        nic->addBodyWidget(authorName, row, 1);

        ElidedLabel* filepath = new ElidedLabel(this);
        filepath->setFullText(query.value(2).toString());
        filepath->setAlignment(Qt::AlignRight);
        nic->addBodyWidget(filepath, row, 2);

        ElidedLabel* seeableness = new ElidedLabel(this);
        if(query.value(3).toBool() == true)
        {
            seeableness->setFullText("Public");
        }
        else
        {
            seeableness->setFullText("Private");
        }
        seeableness->setAlignment(Qt::AlignCenter);
        nic->addBodyWidget(seeableness, row, 3);

        ElidedLabel* creationTime = new ElidedLabel(this);
        creationTime->setFullText(query.value(4).toString());
        creationTime->setAlignment(Qt::AlignRight);
        nic->addBodyWidget(creationTime, row, 4);

        nic->setRowIndex(row, query.value(5).toInt());

        row++;
    }

    nic->updateWidths();
    nic->checkScrollbars();
//*/
}

void songs_screen::deletePopup(const QString &text, const int index)
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
        //delete
        QSqlQuery query;
        query.prepare(
            "DELETE FROM songs WHERE id = (?)"
            );
        query.bindValue(0, index);
        if(!query.exec())
        {
            deletePopup("Database Error", 0);
            return;
        }
        //refresh columns
        nic->clearBody();
        setupBody();
        qDebug() << "deleted" << index;
    }
}

