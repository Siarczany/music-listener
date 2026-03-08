#include "hiddenwidget.h"

HiddenWidget::HiddenWidget(QWidget* target, QObject *parent)
    : QObject(parent)
    , target(target)
{

}

int HiddenWidget::width()
{
    return target->width();
}

void HiddenWidget::setFixedWidth(const int width)
{
    target->setFixedWidth(width);
}
