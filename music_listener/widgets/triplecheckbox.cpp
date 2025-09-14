#include "triplecheckbox.h"

#include <QPainter>
#include <QPainterPath>
#include <QStyleOptionButton>

TripleCheckBox::TripleCheckBox(QWidget *parent) :
    QCheckBox(parent)
{
    //setTristate(true);
    //setText("asddsa");
}

TripleCheckBox::~TripleCheckBox()
{

}

TripleCheckBox::state TripleCheckBox::checkState()
{
    return internalState;
}

void TripleCheckBox::setText(const QString &text)
{
    QCheckBox::setText(text);
}

void TripleCheckBox::nextCheckState()
{
    switch(internalState)
    {
    case state::whatever:
    {
        internalState = state::no;
        break;
    }
    case state::no:
    {
        internalState = state::yes;
        break;
    }
    case state::yes:
    {
        internalState = state::whatever;
        break;
    }
    }
}

void TripleCheckBox::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QStyleOptionButton option;
    initStyleOption(&option);

    QPainter painter(this);

    QStyleOptionButton labelOption(option);
    labelOption.state &= ~QStyle::State_On;
    labelOption.state &= ~QStyle::State_NoChange;
    style()->drawControl(QStyle::CE_CheckBox, &labelOption, &painter, this);
    QRect indicatorRect = style()->subElementRect(QStyle::SE_CheckBoxIndicator, &option, this);

    switch(internalState)
    {
    case state::no:
    {
        QPixmap checkImg(":/icons/icons/minus.png");
        painter.drawPixmap(indicatorRect.adjusted(1, 1, -1, -1), checkImg);
        break;
    }
    case state::yes:
    {
        QPixmap checkImg(":/icons/icons/plus.png");
        painter.drawPixmap(indicatorRect.adjusted(1, 1, -1, -1), checkImg);
        break;
    }
    default:
    {
        break;
    }
    }
}
