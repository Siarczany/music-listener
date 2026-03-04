#include "authors.h"

AuthorsList::AuthorsList(QWidget *parent)
    : HiddenWidget(parent)
    , layout(new QVBoxLayout(this))
    , area(new QScrollArea(this))
{
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(area);
}

AuthorsList::~AuthorsList()
{

}
