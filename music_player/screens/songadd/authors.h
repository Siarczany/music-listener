#ifndef SONGADD_AUTHORSLIST_H
#define SONGADD_AUTHORSLIST_H

#include "widgets/hideablewidget/hiddenwidget.h"
#include <QScrollArea>
#include "widgets/hideablewidget/hideablewidget.h"

//namespace SongAdd
//{

class AuthorsList : public HiddenWidget
{
    Q_OBJECT
public:
    AuthorsList(QWidget* parent = nullptr);
    ~AuthorsList();
private:
    QVBoxLayout* layout;
    QScrollArea* area;
};

//} // namespace SongAdd

#endif // SONGADD_AUTHORSLIST
