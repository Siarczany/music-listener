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
}

testowanie::~testowanie()
{

}



editScreen::editScreen(QWidget *parent) :
    QWidget(parent)
    , layout(new QVBoxLayout(this))
{
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    //QVBoxLayout* screenLayout = new QVBoxLayout(this);
    QWidget* container = new QWidget(this);
    container->setLayout(layout);

    QVBoxLayout* screenLayout = new QVBoxLayout(this);
    screenLayout->setContentsMargins(0, 0, 0, 0);
    screenLayout->setSpacing(0);
    screenLayout->addWidget(container, 0, Qt::AlignCenter);

}

editScreen::~editScreen()
{

}

void editScreen::addLabelLineEdit(QLabel *label,
                                  QLineEdit *lineEdit,
                                  const QString name,
                                  const QString toolTip,
                                  const int width)
{
    label->setText(name);

    label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    lineEdit->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    label->setToolTip(toolTip);
    lineEdit->setToolTip(toolTip);

    lineEdit->setMinimumWidth(width);

    layout->addWidget(label);
    layout->addWidget(lineEdit);

    layout->setAlignment(label, Qt::AlignHCenter);
    layout->setAlignment(lineEdit, Qt::AlignHCenter);

    qDebug() << layout->sizeHint();
}

void editScreen::addWidget(QWidget *widget, const int width)
{
    widget->setMinimumWidth(width);

    layout->addWidget(widget, 0, Qt::AlignHCenter);
}

void editScreen::addLayout(QLayout *layout, const int width)
{
    QWidget* container = new QWidget(this);
    container->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    container->setLayout(layout);

    addWidget(container, width);
}
