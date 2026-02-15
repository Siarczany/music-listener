#ifndef FORM_H
#define FORM_H

#include "screen.h"

#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>

#include "widgets/nicelineedit/nicelineedit.h"

class Form : public Screen
{
    Q_OBJECT

private:
    QVBoxLayout* layout;

    const int width = 200;



public:
    Form(QWidget* parent = nullptr);

    QWidget* addWidget(QWidget *widget, int stretch = 0, Qt::Alignment alignment = Qt::AlignHCenter);

    QLineEdit* addTextField(QString text, QString toolTipText = QString(), int stretch = 0, Qt::Alignment = Qt::AlignHCenter);

    QPushButton* addBackButton();
};

#endif // FORM_H
