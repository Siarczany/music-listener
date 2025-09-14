#ifndef SONGS_TAG_ADD_SCREEN_H
#define SONGS_TAG_ADD_SCREEN_H

#include <QWidget>
#include <QSqlDatabase>
#include "widgets/suggestionlineedit.h"

namespace Ui {
class songs_tag_add_screen;
}

class SongsTagAddScreen : public QWidget
{
    Q_OBJECT

public:
    explicit SongsTagAddScreen(QWidget *parent = nullptr, QSqlDatabase* database = nullptr, bool isGuest = false, int userId = 0, int songId = 0);
    ~SongsTagAddScreen();

signals:
    toSongsTagsScreen(bool isGuest, int userId, int songId);

private:
    Ui::songs_tag_add_screen *ui;
    QSqlDatabase* database;
    bool isGuest;
    int userId;
    int songId;

    SuggestionLineEdit* sle;

    void showSongsTags();

    void setupSLE();
    QStringList nameQuery(const QString& text);

    int tagId();
    void addTag();
};

#endif // SONGS_TAG_ADD_SCREEN_H
