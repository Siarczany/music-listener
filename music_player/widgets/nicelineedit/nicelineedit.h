#ifndef NICELINEEDIT_H
#define NICELINEEDIT_H

//#include "resizablelineedit.h"
#include "resizablelineedit/resizablelineedit.h"
#include "widgets/scrollablelabel/scrollablelabel.h"
#include "suggestionlinedit/suggestionlineedit.h"

class NiceLineEdit : public QWidget
{
    Q_OBJECT

public:
    enum class LineEdit
    {
          Resizable
        , Suggestion
    };
    NiceLineEdit(QWidget* parent = nullptr, LineEdit type = LineEdit::Resizable);
    NiceLineEdit(const QString& text, QWidget* parent = nullptr, LineEdit type = LineEdit::Resizable);
    ~NiceLineEdit();
    void setLabel(const QString& text);
    void setText(const QString& text);
    void setToolTip(const QString& text);
    const QString text();

    ResizableLineEdit* getLineEdit() const;

signals:
    void textChanged(const QString& text);
private:
    ScrollableLabel* label;
    ResizableLineEdit* lineEdit;
    QVBoxLayout* layout;
};

#endif // NICELINEEDIT_H
