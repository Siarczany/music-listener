#ifndef TAGINPUT_H
#define TAGINPUT_H

#include "widgets/listinput/listinput.h"

class TagInput : public ListInput
{
    Q_OBJECT
public:
    TagInput(QWidget* parent = nullptr);
    ~TagInput();
    QStringList getList() const;
private:

};

#endif // TAGINPUT
