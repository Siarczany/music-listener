#include "songs_tag_edit_screen.h"
#include "ui_songs_tag_edit_screen.h"

songs_tag_edit_screen::songs_tag_edit_screen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::songs_tag_edit_screen)
{
    ui->setupUi(this);
}

songs_tag_edit_screen::~songs_tag_edit_screen()
{
    delete ui;
}
