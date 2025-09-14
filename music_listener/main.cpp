#include "mainwindow.h"

#include <QApplication>
#include <QtSql>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("music_player_db.db");

    if(!db.open())
    {
        return -1;
    }


    //https://sqlite.org/lang_createtable.html

    QSqlQuery query;
    query.prepare("CREATE TABLE IF NOT EXISTS users ("
                  "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                  "login TEXT NOT NULL,"
                  "password TEXT NOT NULL,"
                  "name TEXT NOT NULL,"
                  "created_at TEXT NOT NULL" // forgored to put UNIQUE or some shit in this table that binds(?) login and id or something idk
                  ")");
    if(!query.exec())
    {
        qDebug() << "failed at creating table users";
    }
    query.prepare("CREATE TABLE IF NOT EXISTS authors ("
                  "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                  "name TEXT NOT NULL,"
                  "description TEXT,"
                  "owner REFERENCES users(id) ON DELETE RESTRICT,"
                  "is_public INTEGER NOT NULL,"
                  "created_at TEXT NOT NULL"
                  ")");
    if(!query.exec())
    {
        qDebug() << "failed at creatint table authors";
    }
    query.prepare("CREATE TABLE IF NOT EXISTS songs ("
                  "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                  "name TEXT NOT NULL,"
                  "filename TEXT NOT NULL,"
                  "author REFERENCES authors(id) ON DELETE RESTRICT,"
                  "owner REFERENCES users(id) ON DELETE RESTRICT,"
                  "is_public INTEGER NOT NULL,"
                  "created_at TEXT NOT NULL"
                  ")");
    if(!query.exec())
    {
        qDebug() << "failed at creating table songs";
    }
    query.prepare("CREATE TABLE IF NOT EXISTS user_configurations ("
                  "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                  "owner REFERENCES users(id) ON DELETE RESTRICT,"
                  "name TEXT NOT NULL,"
                  "volume REAL NOT NULL,"
                  "time_inbetween INTEGER NOT NULL"
                  ")");
    if(!query.exec())
    {
        qDebug() << "failed at creating table user_configurations";
    }
    query.prepare("CREATE TABLE IF NOT EXISTS playlists ("
                  "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                  "name TEXT NOT NULL,"
                  "owner REFERENCES users(id) ON DELETE RESTRICT,"
                  "created_at TEXT NOT NULL"
                  ")");
    if(!query.exec())
    {
        qDebug() << "failed at creating table playlists";
    }
    query.prepare("CREATE TABLE IF NOT EXISTS playlist_contents ("
                  "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                  "song REFERENCES songs(id) ON DELETE RESTRICT,"
                  "playlist REFERENCES playlists(id) ON DELETE CASCADE,"
                  "created_at TEXT NOT NULL"
                  ")");
    if(!query.exec())
    {
        qDebug() << "failed at creating table playlist_contents";
    }
    query.prepare("CREATE TABLE IF NOT EXISTS tags ("
                  "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                  "name TEXT NOT NULL,"
                  "owner REFERENCES users(id) ON DELETE RESTRICT,"
                  "created_at TEXT NOT NULL"
                  ")");
    if(!query.exec())
    {
        qDebug() << "failed at creating table tags";
    }
    query.prepare("CREATE TABLE IF NOT EXISTS song_tags ("
                  "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                  "song REFERENCES songs(id) ON DELETE RESTRICT,"
                  "tag REFERENCES tags(id) ON DELETE RESTRICT,"
                  "created_at TEXT NOT NULL"
                  ")");
    if(!query.exec())
    {
        qDebug() << "failed at creating table song_tags";
    }
    query.~QSqlQuery();

    MainWindow w(nullptr, &db);
    w.show();
    return a.exec();
}
