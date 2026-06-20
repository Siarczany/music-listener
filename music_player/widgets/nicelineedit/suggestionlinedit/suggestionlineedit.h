#ifndef SUGGESTIONLINEEDIT_H
#define SUGGESTIONLINEEDIT_H

#include <QLineEdit>
#include <functional>
#include "suggestionpopup.h"
#include "widgets/nicelineedit/mylineedit/mylineedit.h"

// line edit that displays available texts that match hat you typed and you can select them
class SuggestionLineEdit : public ResizableLineEdit
{
    Q_OBJECT
public:
    SuggestionLineEdit(QWidget* parent = nullptr);
    ~SuggestionLineEdit();

    // for setting a custom query
    void setQuery(std::function<QStringList(const QString&)> func);

protected:
    // when focusing out of lineedit we want to hide the popup as it can cover things
    void focusOutEvent(QFocusEvent* event) override;

signals:
    // signal for upper widgets that something has been choosen
    void choosen();

private:
    // popup that pops up xd
    SuggestionPopup* popup;

    // manages the contents of the popup
    void setupPopup(const QString& text);

    // function pointer holding user query
    std::function<QStringList(const QString&)> queryFunc = nullptr;
};

#endif //SUGGESTIONLINEEDIT
