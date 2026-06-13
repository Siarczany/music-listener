#ifndef HIDEABLELIST_H
#define HIDEABLELIST_H

#include "widgets/hideablewidget/hideablewidget.h"

class HideableList : public QWidget
{
    Q_OBJECT
public:
    HideableList(QWidget* parent = nullptr);
    ~HideableList();
private:
};

#endif // HIDEABLELIST
