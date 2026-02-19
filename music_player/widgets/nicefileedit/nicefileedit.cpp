#include "nicefileedit.h"
#include <QFileDialog>

NiceFileEdit::NiceFileEdit(QWidget *parent)
    : file_nle(new NiceLineEdit(this))
    , select_pb(new QPushButton(this))
    , layout(new QVBoxLayout(this))
{
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(file_nle, 0, Qt::AlignHCenter);
    layout->addWidget(select_pb, 0, Qt::AlignHCenter);

    select_pb->setText("Wybierz plik");
    select_pb->setFixedWidth(100);

    connect(select_pb, &QPushButton::clicked, this, [this](){
        filepath = QFileDialog::getOpenFileName(this, "Open file", filepath, "Audio Files (*.mp3 *.wav);;All Files (*)");
        //QFileInfo fileName(filepath);
        file_nle->setText(filepath);
    });

    connect(file_nle, &NiceLineEdit::textChanged, this, &NiceFileEdit::textChanged);
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
    file_nle->setLabel(text);
}

void NiceFileEdit::setToolTip(const QString &text)
{
    file_nle->setToolTip(text);
    select_pb->setToolTip("Wybierz plik");
}
