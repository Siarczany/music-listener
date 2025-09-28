#include "testowanie.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QMenu>
#include <QPushButton>

#include "widgets/playlistlabel.h"


testowanie::testowanie(QWidget *parent) :
    editScreen(parent)
    , le1(new QLineEdit(this))
    , le2(new QLineEdit(this))
{
    QLabel* l1 = new QLabel(this);

    addLabelLineEdit(l1, le1, "asd", "asddsa", 400);

    QLabel* l2 = new QLabel(this);

    addLabelLineEdit(l2, le2, "dsa", "dsaasd", 200);

    QLabel* l3 = new QLabel(this);
    l3->setText("inside");

    QPushButton* pb1 = new QPushButton(this);
    pb1->setText("inside");

    QHBoxLayout* insideLayout = new QHBoxLayout;
    insideLayout->addWidget(l3);
    insideLayout->addWidget(pb1);

    addLayout(insideLayout, 100);

    addEditStuff(300);
}

testowanie::~testowanie()
{

}

void testowanie::editQuery()
{
    setUserOutputText("asdd");
}

void testowanie::loadQuery()
{

}



