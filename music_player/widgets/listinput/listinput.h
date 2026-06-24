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
    // this widget is used in TagInput as a hidden widget but this widget
    //  already has a label on top and hideable one adds a label so it looks funny
    //  and this requires a ScrollableLabel but HideableWidget wants
    //  ClickableLabel so this takes in a ClickableLabel which works or something
    //  idk
    ListInput(ScrollableLabel* label, QWidget* parent = nullptr);

    ~ListInput();

    // sets query for the suggstion line edit
    void setQuery(std::function<QStringList(const QString&)> function);

    // set labels
    void setInputLabel(const QString& text);
    void setListLabel(const QString& text);

    // gets list from ItemList
    QStringList getList() const;

    // getters for inner widgets
    //  only getNiceLineEdit is used but it's nice to have I guess idk
    NiceLineEdit* getNiceLineEdit() const;
    ItemList* getItemList() const;
    HideableWidget* getHideable() const;
signals:
    // signal for upper widgets
    void sizeChanged();
private:
    QVBoxLayout* layout;

    NiceLineEdit* input;
    SuggestionLineEdit* suggestionInput;

    ItemList* list;
    HideableWidget* hideable;

    // constructor logic because we have 2 constructots
    void construct();

    // sets the width of the list label because it has 2 resizable things above
    //  and below so I couldn't decide which size should it take
    //  I settled on the max size of the two
    // possible improvement is to shrink() the label after getting the max size
    void setListLabelWidth();

};

#endif // LISTINPUT
