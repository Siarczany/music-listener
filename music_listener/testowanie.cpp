#include "testowanie.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QMenu>

#include "widgets/playlistlabel.h"


testowanie::testowanie(QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    QLabel* l = new QLabel("asddsa", this);

    PlaylistLabel* i = new PlaylistLabel();
    i->setText("asddsa");
    layout->addWidget(i);
    layout->addWidget(l);
}

testowanie::~testowanie()
{

}


