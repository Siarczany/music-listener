#ifndef SONGS_TAG_EDIT_SCREEN_H
#define SONGS_TAG_EDIT_SCREEN_H

#include <QWidget>

namespace Ui {
class songs_tag_edit_screen;
}

class songs_tag_edit_screen : public QWidget
{
    Q_OBJECT

public:
    explicit songs_tag_edit_screen(QWidget *parent = nullptr);
    ~songs_tag_edit_screen();

private:
    Ui::songs_tag_edit_screen *ui;
};

#endif // SONGS_TAG_EDIT_SCREEN_H
