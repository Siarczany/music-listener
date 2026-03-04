#include "nicelineedit.h"

NiceLineEdit::NiceLineEdit(QWidget* parent, LineEdit type)
    : QWidget(parent)
    , label(new ScrollableLabel(this))
    //, lineEdit(new ResizableLineEdit(this))
    , layout(new QVBoxLayout(this))
{
    switch(type)
    {
        case LineEdit::Resizable:
        {
            lineEdit = new ResizableLineEdit(this);
            break;
        }
        case LineEdit::Suggestion:
        {
            lineEdit = new SuggestionLineEdit(this);
            break;
        }
        default:
        {
            lineEdit = new ResizableLineEdit(this);
        }
    }

    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(label);
    layout->addWidget(lineEdit);

    connect(lineEdit, &ResizableLineEdit::sizeChanged, this, [this]()
            {
        label->setFixedWidth(lineEdit->width());
    });

    connect(lineEdit, &ResizableLineEdit::textChanged, this, &NiceLineEdit::textChanged);
}

NiceLineEdit::NiceLineEdit(const QString &text, QWidget *parent, LineEdit type)
    : NiceLineEdit(parent, type)
{
    label->setFullText(text);
    label->setToolTip(text);
    lineEdit->setToolTip(text);
}

NiceLineEdit::~NiceLineEdit()
{

}

void NiceLineEdit::setLabel(const QString &text)
{
    label->setFullText(text);
}

void NiceLineEdit::setText(const QString &text)
{
    lineEdit->setText(text);
}

void NiceLineEdit::setToolTip(const QString &text)
{
    label->setToolTip(text);
    lineEdit->setToolTip(text);
}

const QString NiceLineEdit::text()
{
    return lineEdit->text();
}

ResizableLineEdit *NiceLineEdit::getLineEdit() const
{
    return lineEdit;
}
