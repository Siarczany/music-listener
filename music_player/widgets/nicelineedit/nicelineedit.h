#ifndef NICELINEEDIT_H
#define NICELINEEDIT_H

//#include "resizablelineedit.h"
#include "mylineedit/mylineedit.h"
#include "widgets/scrollablelabel/scrollablelabel.h"
#include "suggestionlinedit/suggestionlineedit.h"
#include <QVBoxLayout>

// nice line edit that has a label and a line edit
//  and can have a suggestion box below if needed
class NiceLineEdit : public QWidget
{
    Q_OBJECT

public:
    enum class LineEdit
    {
          Resizable
        , Suggestion
    };

    // 2 standard constructors but the 2. one already sets the label
    NiceLineEdit(QWidget* parent = nullptr, LineEdit type = LineEdit::Resizable);
    NiceLineEdit(const QString& text, QWidget* parent = nullptr, LineEdit type = LineEdit::Resizable);

    // in tag input I want to hide line edit and only show the label
    //  but this has label build it so here's the constructor that takes in an existing
    //  label and uses it, that way label can be both in here as here it doean't do
    //  anything except resizing maybe and in hideablewidget it can be clicked :)
    NiceLineEdit(ScrollableLabel* label, QWidget* parent = nullptr, LineEdit type = LineEdit::Resizable);

    ~NiceLineEdit();

    // sets label
    void setLabel(const QString& text);

    // sets line edit text
    void setText(const QString& text);

    // sets tooltip for both a label and line edit
    void setToolTip(const QString& text);

    // gets text from line edit
    const QString text();

    // getters for widgets
    //  only getLabel is used by tapInput but getLineEdit is here as wwell xd
    // in theory it would be nice to have getters like this in every class but why
    //  bother
    ResizableLineEdit* getLineEdit() const;
    ScrollableLabel* getLabel() const;

signals:
    // for upper widget
    void textChanged(const QString& text);
private:
    ScrollableLabel* label;
    ResizableLineEdit* lineEdit;
    QVBoxLayout* layout;

    // as we have many constructors but they have like 1 line of idfference
    //  the main logic is in here
    void construct(LineEdit type);
};

#endif // NICELINEEDIT_H
