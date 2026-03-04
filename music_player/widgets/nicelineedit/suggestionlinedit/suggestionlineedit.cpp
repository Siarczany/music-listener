#include "suggestionlineedit.h"
#include "suggestionpopup.h"

#include <QApplication>

SuggestionLineEdit::SuggestionLineEdit(QWidget *parent) :
    ResizableLineEdit(parent)
    , popup(new SuggestionPopup(this))
{
    popup->hide();

    connect(this, &QLineEdit::textChanged, this, &SuggestionLineEdit::setupPopup);

    connect(popup, &SuggestionPopup::itemChosen, this, [this](const QString& text){
        this->setText(text);
        emit choosen();
    });

}

SuggestionLineEdit::~SuggestionLineEdit()
{

}

void SuggestionLineEdit::setQuery(std::function<QStringList (const QString &)> func)
{
    queryFunc = std::move(func);
}

void SuggestionLineEdit::focusOutEvent(QFocusEvent *event)
{
    if (popup) {
        popup->hide();
    }
    QLineEdit::focusOutEvent(event);
}

void SuggestionLineEdit::setupPopup(const QString& text)
{
    if(this->text().isEmpty())
    {
        popup->hide();
        return;
    }

    QStringList suggestions;
    if(queryFunc)
    {
        suggestions = queryFunc(text);
    }
    popup->clear();

    popup->addItems(suggestions);

    if(!suggestions.isEmpty())
    {
        popup->setVisible(true);
        QApplication::processEvents();
        QPoint below = mapToGlobal(QPoint(0, this->height()));
        popup->move(below);
        int rowHeight = popup->sizeHintForRow(0);
        int rows = suggestions.size();
        int marginTop = popup->contentsMargins().top();
        int marginBottom = popup->contentsMargins().bottom();
        popup->resize(this->width(), marginTop + rows * rowHeight + marginBottom);
        popup->show();
    }
    else
    {
        popup->hide();
    }
}

const QStringList SuggestionLineEdit::queryDatabase(const QString &text)
{
    QStringList list;
    //list << "a" << "b" << "ab" << "c" << "ac" << "bc" << "abc" << "d";
    for(int i = 0; i<text.size(); i++)
    {
        list << text;
    }

    return list;
}
