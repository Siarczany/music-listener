#include "listinput.h"

ListInput::ListInput(QWidget *parent)
    : QWidget(parent)
    , layout(new QVBoxLayout(this))
    , input(new NiceLineEdit(this, NiceLineEdit::LineEdit::Suggestion))
    , list(new ItemList(this))
{
    construct();
}

ListInput::ListInput(ScrollableLabel *label, QWidget *parent)
    : QWidget(parent)
    , layout(new QVBoxLayout(this))
    , input(new NiceLineEdit(label, this, NiceLineEdit::LineEdit::Suggestion))
    , list(new ItemList(this))
{
    construct();
}



ListInput::~ListInput()
{

}

void ListInput::setQuery(std::function<QStringList (const QString &)> function)
{
    suggestionInput->setQuery(function);
}

void ListInput::setInputLabel(const QString &text)
{
    input->setLabel(text);
}

void ListInput::setListLabel(const QString &text)
{
    hideable->setText(text);
    list->setLabelText(text);
}

void ListInput::setInSight(const bool visibility)
{
    hideable->setInSight(visibility);
}

QStringList ListInput::getList() const
{
    return list->getList();
}

NiceLineEdit *ListInput::getInput() const
{
    return input;
}

ItemList *ListInput::getListWidget() const
{
    return list;
}

HideableWidget *ListInput::getHideable() const
{
    return hideable;
}

void ListInput::construct()
{
    hideable = new HideableWidget(list, list->getHiddenWidget(), this);
    suggestionInput = static_cast<SuggestionLineEdit*>(input->getLineEdit());
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    layout->addWidget(input, 0, Qt::AlignHCenter);
    layout->addWidget(hideable, 0, Qt::AlignHCenter);

    //setInSight(false);
    //hideable->setVisible(false);
    hideable->setInSightFull(false);

    connect(suggestionInput, &SuggestionLineEdit::textChanged,
            this, [this](){
                list->addFirst(suggestionInput->text());
                hideable->setInSightFull(true);
            });
    connect(suggestionInput, &SuggestionLineEdit::choosen,
            this, [this](){
                list->add(suggestionInput->text());
                suggestionInput->clear();
                hideable->setInSightFull(true);
            });
    connect(suggestionInput, &SuggestionLineEdit::returnPressed,
            this, [this](){
                list->add(suggestionInput->text());
                suggestionInput->clear();
                hideable->setInSightFull(true);
            });
    connect(list, &ItemList::deleted,
            this, [this](){
                if(list->count() == 0)
                {
                    hideable->setInSightFull(false);
                }
            });
    connect(list, &ItemList::sizeChanged,
            this, [this](){
                qDebug() << "list changed" << list->width() << hideable->getLabel()->width();
                setListLabelWidth();
            });
    connect(suggestionInput, &SuggestionLineEdit::sizeChanged,
            this, [this](){
                //qDebug() << "suggestion changed" << suggestionInput->width() << hideable->getLabel()->width();
                setListLabelWidth();
            });
}

void ListInput::setListLabelWidth()
{
    const int listWidth = list->width();
    const int inputWidth = suggestionInput->width();

    const int max = std::max(listWidth, inputWidth);

    hideable->getLabel()->setFixedWidth(max);
}
