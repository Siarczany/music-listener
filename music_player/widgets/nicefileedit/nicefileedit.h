#ifndef NICEFILEEDIT_H
#define NICEFILEEDIT_H

#include <QWidget>
#include "widgets/nicelineedit/nicelineedit.h"
#include <QPushButton>

// nice line edit but with a button to open QFileDialog and select a file
class NiceFileEdit : public QWidget
{
    Q_OBJECT

public:
    // basic constcutor
    NiceFileEdit(QWidget* parent = nullptr);

    // sets the label text as well
    NiceFileEdit(const QString& text, QWidget* parent = nullptr);

    ~NiceFileEdit();

    // sets nice line edit label
    void setText(const QString& text);

    // sets tool tip for nice line edit as well as
    //  a constant one for the select button
    void setToolTip(const QString& text);

signals:
    void textChanged(const QString& text);
private:
    QVBoxLayout* layout;
    NiceLineEdit* niceLineEdit;
    QPushButton* pushButton;
    QString filepath = "";
};

#endif // NICEFILEEDIT
