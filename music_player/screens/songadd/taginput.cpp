#include "taginput.h"

#include <QStringList>

TagInput::TagInput(QWidget *parent)
    : ListInput(parent)
{
    setInputLabel("Tag");
    setListLabel("Tagi");
    setQuery([this](const QString& text){
        QStringList all;
        all << "1a" << "1b" << "2" << "3" << "5" << "8" << "13" << "21";
        QStringList ret;
        for(QString& str : all)
        {
            if(rand()%3 == 0)
            {
                ret << str;
            }
        }
        return ret;
    });
}

TagInput::~TagInput()
{

}

QStringList TagInput::getList() const
{
    return ListInput::getList();
}
