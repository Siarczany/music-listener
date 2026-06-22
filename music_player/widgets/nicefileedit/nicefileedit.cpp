#include "nicefileedit.h"
#include <QFileDialog>

NiceFileEdit::NiceFileEdit(QWidget *parent)
    : QWidget(parent)
    , niceLineEdit(new NiceLineEdit(this))
    , pushButton(new QPushButton(this))
    , layout(new QVBoxLayout(this))
{
    // layout stuff
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(niceLineEdit, 0, Qt::AlignHCenter);
    layout->addWidget(pushButton, 0, Qt::AlignHCenter);

    pushButton->setText("Wybierz plik");
    // select button has fixed size
    pushButton->setFixedWidth(100);

    connect(pushButton, &QPushButton::clicked, this, [this](){
        filepath = QFileDialog::getOpenFileName(this, "Open file", filepath, "Audio Files (*.mp3 *.wav);;All Files (*)");
        niceLineEdit->setText(filepath);
    });

    connect(niceLineEdit, &NiceLineEdit::textChanged, this, &NiceFileEdit::textChanged);
}

NiceFileEdit::NiceFileEdit(const QString &text, QWidget *parent)
    : NiceFileEdit(parent)
{
    setText(text);
    setToolTip(text);
}

NiceFileEdit::~NiceFileEdit()
{

}

void NiceFileEdit::setText(const QString &text)
{
    niceLineEdit->setLabel(text);
}

void NiceFileEdit::setToolTip(const QString &text)
{
    niceLineEdit->setToolTip(text);
    pushButton->setToolTip("Wybierz plik");
}
