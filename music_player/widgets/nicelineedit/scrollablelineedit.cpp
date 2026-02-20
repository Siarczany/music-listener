#include "scrollablelineedit.h"
#include <private/qlineedit_p.h>

ScrollableLineEdit::ScrollableLineEdit(QWidget *parent)
    : QLineEdit(parent)
{

}

ScrollableLineEdit::~ScrollableLineEdit()
{

}

void ScrollableLineEdit::wheelEvent(QWheelEvent *event)
{
    //Q_D(QLineEdit);
}
