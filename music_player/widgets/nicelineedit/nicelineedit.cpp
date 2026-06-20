#include "nicelineedit.h"

// basic constructor
NiceLineEdit::NiceLineEdit(QWidget* parent, LineEdit type)
    : QWidget(parent)
    , label(new ScrollableLabel(this))
    , layout(new QVBoxLayout(this))
{
    construct(type);
}

// basic constructor but sets label as well as tooltips
NiceLineEdit::NiceLineEdit(const QString &text, QWidget *parent, LineEdit type)
    : NiceLineEdit(parent, type)
{
    setLabel(text);
    setToolTip(text);
}

// constructor that takes in an already existing label
//  why is label in a fucking comment blue dxafafcbsaf
NiceLineEdit::NiceLineEdit(ScrollableLabel *label, QWidget *parent, LineEdit type)
    : QWidget(parent)
    , label(label)
    , layout(new QVBoxLayout(this))
{
    label->setParent(this);
    construct(type);
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

ScrollableLabel *NiceLineEdit::getLabel() const
{
    return label;
}

void NiceLineEdit::construct(LineEdit type)
{
    // based of the type create a corresponding lineedit
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

    // layout stuff
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(label);
    layout->addWidget(lineEdit);

    // resize the label along with the line edit
    connect(lineEdit, &ResizableLineEdit::sizeChanged, this, [this]()
            {
                label->setFixedWidth(lineEdit->width());
            });

    connect(lineEdit, &ResizableLineEdit::textChanged, this, &NiceLineEdit::textChanged);
}


