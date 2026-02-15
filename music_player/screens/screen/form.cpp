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

QLineEdit *Form::addTextField(QString text, QString toolTipText, int stretch, Qt::Alignment alignment)
{
    QLabel* label = new QLabel(this);
    label->setAlignment(Qt::AlignHCenter);
    label->setText(text);
    label->setToolTip(toolTipText);
    //label->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    QLineEdit* lineEdit = new QLineEdit(this);
    lineEdit->setToolTip(toolTipText);
    lineEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    QVBoxLayout* fieldLayout = new QVBoxLayout(this);
    fieldLayout->setContentsMargins(0, 0, 0, 0);
    fieldLayout->setSpacing(0);

    fieldLayout->addWidget(label, 0, Qt::AlignHCenter);
    fieldLayout->addWidget(lineEdit, 0, Qt::AlignHCenter);

    QWidget* field = new QWidget(this);
    field->setLayout(fieldLayout);

    layout->addWidget(field, stretch, alignment);

    return lineEdit;
}

QPushButton *Form::addBackButton()
{
    QPushButton* back_pb = new QPushButton(this);
    back_pb->setText("Back");

    addWidget(back_pb);
    return back_pb;
}
