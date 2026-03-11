#ifndef LISTINPUT_H
#define LISTINPUT_H

#include <QWidget>
#include <QVBoxLayout>

#include "listitem.h"
#include "listview.h"
#include "itemlist.h"

#include "widgets/nicelineedit/nicelineedit.h"
class ListInput : public QWidget
{
    Q_OBJECT
public:
    ListInput(QWidget* parent = nullptr);
    ~ListInput();

    void setQuery(std::function<QStringList(const QString&)> function);
    void setInputLabel(const QString& text);
    void setListLabel(const QString& text);
    void setInSight(const bool visibility);
private:
    QVBoxLayout* layout;
    NiceLineEdit* input;
    SuggestionLineEdit* suggestionInput;
    ItemList* list;
    HideableWidget* hideable;
};

#endif // LISTINPUT
