#ifndef SONGS_EDIT_SCREEN_H
#define SONGS_EDIT_SCREEN_H

#include <QWidget>
#include <QSqlDatabase>
#include "widgets/suggestionlineedit.h"

namespace Ui {
class songs_edit_screen;
}

class SongsEditScreen : public QWidget
{
    Q_OBJECT

public:
    explicit SongsEditScreen(QWidget *parent = nullptr, QSqlDatabase* database = nullptr, bool isGuest = false, int userId = 0, int songId = 0);
    ~SongsEditScreen();

signals:
    toSongsScreen();
    updateSongId(int songId);

private:
    Ui::songs_edit_screen *ui;
    QSqlDatabase* db;
    bool isGuest;
    int userId;
    int songId;

    void showSongs();

    SuggestionLineEdit* sle;
    QString fullFilePath;

    void setupUi();

    void handleFileDialog();
    void editSong();

    QStringList artistQuery(const QString& text);
};

#endif // SONGS_EDIT_SCREEN_H
