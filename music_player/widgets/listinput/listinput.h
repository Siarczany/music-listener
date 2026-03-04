#ifndef LISTINPUT_H
#define LISTINPUT_H

#include <QWidget>
#include <QVBoxLayout>
//#include "widgets/suggestionlinedit/suggestionlineedit.h"

class ListInput : public QWidget
{
    Q_OBJECT
public:
    ListInput(QWidget* parent = nullptr);
    ~ListInput();
private:
    QVBoxLayout* layout;
    //SuggestionLineEdit* input_sle;
protected:

};

#endif // LISTINPUT
