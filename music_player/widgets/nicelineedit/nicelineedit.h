#ifndef NICELINEEDIT_H
#define NICELINEEDIT_H

#include "resizablelineedit.h"
#include "scrollablelabel.h"

class NiceLineEdit : public QWidget
{
    Q_OBJECT

public:
    NiceLineEdit(QWidget* parent = nullptr);
    NiceLineEdit(const QString& text, QWidget* parent = nullptr);
    ~NiceLineEdit();
    void setLabel(const QString& text);
    void setText(const QString& text);
    void setToolTip(const QString& text);
    const QString text();
signals:
    void textChanged(const QString& text);
private:
    ScrollableLabel* label;
    ResizableLineEdit* rle;
    QVBoxLayout* layout;
};

#endif // NICELINEEDIT_H
