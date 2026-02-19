#include "form.h"

#include <QLabel>

Form::Form(QWidget *parent)
    : Screen(parent)
    , layout(new QVBoxLayout(this))
{
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    //this->setLayout(layout);

    QWidget* container = new QWidget(this);
    container->setLayout(layout);
    container->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    QVBoxLayout* screenLayout = new QVBoxLayout(this);
    screenLayout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    screenLayout->addWidget(container, 0, Qt::AlignCenter);
}



QWidget* Form::addWidget(QWidget *widget, int stretch, Qt::Alignment alignment)
{
    layout->addWidget(widget, stretch, alignment);
    return widget;
}

NiceLineEdit *Form::addTextField(const QString &text, const QString &toolTip)
{
    NiceLineEdit* nle = new NiceLineEdit(this);
    nle->setLabel(text);
    nle->setToolTip(toolTip);

    addWidget(nle);

    return nle;
}

QPushButton *Form::addBackButton()
{
    QPushButton* back_pb = new QPushButton(this);
    back_pb->setText("Back");

    addWidget(back_pb);
    return back_pb;
}
