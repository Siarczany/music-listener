#pragma once

#include "widgets/hideablewidget/hideablewidget.h"
#include "widgets/viewbase/viewbase.h"
#include "listview.h"

class ItemList : public QWidget
{
    Q_OBJECT
public:
    ItemList(QWidget* parent = nullptr);
    ~ItemList();

    // hidden widget stuff
    HiddenWidget* getHiddenWidget() const;

    // zwraca ilość elementów w liście
    int count() const;

    // I wanted a behaviour such that the user can type something and not press
    //  enter and if this is the first item it will be added automaticly
    // this function is meant to be connected to text input text changed signal
    void addFirst(const QString& text);

    // this function is meant to be connected to choosing item via suggestion or
    //  by clicking enter
    void add(const QString& text);

    // sets label for the list
    //  we cannot just add 's' because other languages exist xd
    void setLabelText(const QString& text);

    // gets a list of strings tha the user entered
    QStringList getList() const;

signals:
    // resizable widget from ListView carry on
    void sizeChanged();

    // signal from ListView about deletion because we want to fully hide the list
    //  if there are 0 things in it
    void deleted();

protected:
    // for resizable widght and hidden widget
    void resizeEvent(QResizeEvent *event) override;
private:
    QVBoxLayout* layout;

    // hidden widget stuff
    HiddenWidget* hiddenWidget;
    struct HiddenWidgetData
    {
        int width;
    };
    HiddenWidgetData hwd;
    void inSight(bool visibility);

    Model* model;
    ListView* view;

    // we want to display for example "Authors(3)"
    //  so we remember the original text and add "(3)" to it
    QString labelText;

    // to know if the first item has been choosen or not
    bool firstLockedIn = false;

    // refresheses the list and the label
    void refresh();
};
