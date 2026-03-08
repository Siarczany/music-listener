#ifndef SUGGESTIONLINEEDIT_H
#define SUGGESTIONLINEEDIT_H

#include <QLineEdit>
#include <functional>
#include "suggestionpopup.h"
#include "widgets/nicelineedit/mylineedit/mylineedit.h"

class SuggestionLineEdit : public ResizableLineEdit
{
    Q_OBJECT
public:
    SuggestionLineEdit(QWidget* parent = nullptr);
    ~SuggestionLineEdit();

    void setQuery(std::function<QStringList(const QString&)> func);
protected:
    void focusOutEvent(QFocusEvent* event) override;

signals:
    void choosen();

private:
    SuggestionPopup* popup;

    void setupPopup(const QString& text);
    const QStringList queryDatabase(const QString& text);
    std::function<QStringList(const QString&)> queryFunc = nullptr;


};

#endif //SUGGESTIONLINEEDIT
