#include "nicelineedit.h"

NiceLineEdit::NiceLineEdit(QWidget* parent)
    : QWidget(parent)
    , label(new ScrollableLabel(this))
    , rle(new ResizableLineEdit(this))
    , layout(new QVBoxLayout(this))
{
    //label->setFullText(text);
    //label->setToolTip(toolTip);

    //rle->setToolTip(toolTip);

    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(label);
    layout->addWidget(rle);

    connect(rle, &ResizableLineEdit::sizeChanged, this, [this]()
            {
        label->setFixedWidth(rle->width());
    });
}

NiceLineEdit::NiceLineEdit(const QString &text, QWidget *parent)
    : NiceLineEdit(parent)
{
    label->setFullText(text);
    label->setToolTip(text);
    rle->setToolTip(text);
}

NiceLineEdit::~NiceLineEdit()
{

}

void NiceLineEdit::setText(const QString &text)
{
    label->setFullText(text);
}

void NiceLineEdit::setToolTip(const QString &text)
{
    label->setToolTip(text);
    rle->setToolTip(text);
}

const QString NiceLineEdit::text()
{
    return rle->text();
}
