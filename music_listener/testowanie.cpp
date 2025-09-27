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



editScreen::editScreen(QWidget *parent) :
    QWidget(parent)
    , layout(new QVBoxLayout(this))
    , back_pb(new QPushButton(this))
    , userOutput_l(new QLabel(this))
    , edit_pb(new QPushButton(this))
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

    back_pb->setVisible(false);
    edit_pb->setVisible(false);
    userOutput_l->setVisible(false);

    back_pb->setText("Back");
    edit_pb->setText("Edit");

    back_pb->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    edit_pb->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    userOutput_l->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    userOutput_l->setAlignment(Qt::AlignCenter);

    connect(back_pb, &QPushButton::clicked, this, back);
    connect(edit_pb, &QPushButton::clicked, this, editQuery);
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


    connect(lineEdit, QLineEdit::textChanged, this, clearUserOutput);
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

void editScreen::addUserOutput(const QString &text)
{
    QFontMetrics fm(userOutput_l->font());
    int textWidth = fm.horizontalAdvance(text);

    if(textWidth > longestUserOutputWidth)
    {
        longestUserOutputWidth = textWidth;
        userOutput_l->setMinimumWidth(textWidth);
    }
}

void editScreen::loadQuery()
{

}

void editScreen::editQuery()
{

}

void editScreen::clearUserOutput()
{
    userOutput_l->setText("");
}

void editScreen::addEditStuff(const int width)
{
    if(back_pb->isVisible())
    {
        return;
    }

    edit_pb->setMinimumWidth(width);
    back_pb->setMinimumWidth(width);

    layout->addWidget(edit_pb);
    layout->addWidget(userOutput_l);
    layout->addWidget(back_pb);

    layout->setAlignment(edit_pb, Qt::AlignHCenter);
    layout->setAlignment(back_pb, Qt::AlignHCenter);
    layout->setAlignment(userOutput_l, Qt::AlignHCenter);

    back_pb->setVisible(true);
    edit_pb->setVisible(true);
    userOutput_l->setVisible(true);
}

void editScreen::setUserOutputText(const QString &text)
{
    userOutput_l->setText(text);
}
