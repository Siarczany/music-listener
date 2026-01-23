#include "appstate.h"

AppState::AppState(QObject* parent) :
    QObject(parent)
{}

void AppState::setDatabase(QSqlDatabase *database)
{
    this->sql_database = database;
    emit databaseChanged(database);
}

void AppState::setUserId(int userId)
{
    this->user_id = userId;
    emit userIdChanged(userId);
}

void AppState::setPlaylistId(int playlistId)
{
    this->playlist_id = playlistId;
    emit playlistIdChanged(playlistId);
}

void AppState::setSongId(int songId)
{
    this->song_id = songId;
    emit songIdChanged(songId);
}

void AppState::setAuthorId(int authorId)
{
    this->author_id = authorId;
    emit authorIdChanged(authorId);
}

void AppState::setTagId(int tagId)
{
    this->tag_id = tagId;
    emit tagIdChanged(tagId);
}

QSqlDatabase *AppState::database() const
{
    return sql_database;
}

int AppState::userId() const
{
    return user_id;
}

int AppState::playlistId() const
{
    return playlist_id;
}

int AppState::songId() const
{
    return song_id;
}

int AppState::authorId() const
{
    return author_id;
}

int AppState::tagId() const
{
    return tag_id;
}



