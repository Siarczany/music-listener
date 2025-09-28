#ifndef SONGS_ADD_SCREEN_H
#define SONGS_ADD_SCREEN_H

#include <QWidget>
#include <QSqlDatabase>
#include "widgets/suggestionlineedit.h"

namespace Ui {
class songs_add_screen;
}

class songs_add_screen : public QWidget
{
    Q_OBJECT

public:
    explicit songs_add_screen(QWidget *parent = nullptr, QSqlDatabase* database = nullptr, bool isGuest = false, int userId = 0);
    ~songs_add_screen();

signals:
    toSongsScreen();

private:
    Ui::songs_add_screen *ui;
    QSqlDatabase* db;
    bool isGuest;
    int userId;
    SuggestionLineEdit* sle;

    void showSongs();

    QStringList artistQuery(const QString& text);

    QString fullFilePath;
    void handleFileDialog();

    int artistId();

    void addSong();
};

#endif // SONGS_ADD_SCREEN_H
