#ifndef APPSTATE_H
#define APPSTATE_H

#include <QObject>
#include <QtSql/QSqlDatabase>

class AppState : public QObject
{
    Q_OBJECT

private:
    QSqlDatabase* sql_database;
    int user_id;
    int playlist_id;
    int song_id;
    int author_id;
    int tag_id;

signals:
    void databaseChanged(QSqlDatabase* database);
    void userIdChanged(int userId);
    void playlistIdChanged(int playlistId);
    void songIdChanged(int songId);
    void authorIdChanged(int authorId);
    void tagIdChanged(int tagId);

public:
    AppState(QObject* parent = nullptr);

    void setDatabase(QSqlDatabase* database);
    void setUserId(int userId);
    void setPlaylistId(int playlistId);
    void setSongId(int songId);
    void setAuthorId(int authorId);
    void setTagId(int tagId);

    QSqlDatabase* database() const;
    int userId() const;
    int playlistId() const;
    int songId() const;
    int authorId() const;
    int tagId() const;
};

#endif // APPSTATE_H
