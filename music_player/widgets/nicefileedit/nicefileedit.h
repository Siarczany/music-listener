#ifndef NICEFILEEDIT_H
#define NICEFILEEDIT_H

#include <QWidget>
#include "widgets/nicelineedit/nicelineedit.h"
#include <QPushButton>

class NiceFileEdit : public QWidget
{
    Q_OBJECT

public:
    NiceFileEdit(QWidget* parent = nullptr);
    NiceFileEdit(const QString& text, QWidget* parent = nullptr);
    ~NiceFileEdit();
    void setText(const QString& text);
    void setToolTip(const QString& text);
    //const
signals:
    void textChanged(const QString& text);
private:
    NiceLineEdit* file_nle;
    QPushButton* select_pb;
    QVBoxLayout* layout;
    QString filepath = "";
};

#endif // NICEFILEEDIT
