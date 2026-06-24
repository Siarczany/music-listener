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
    // list is inside of hideable
    hideable->setText(text);

    // list text that because we want to display for example "Tags(5)"
    list->setLabelText(text);
}

QStringList ListInput::getList() const
{
    return list->getList();
}

NiceLineEdit *ListInput::getNiceLineEdit() const
{
    return input;
}

ItemList *ListInput::getItemList() const
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

    // hide list at start as there aren't any items inside
    hideable->setInSightFull(false);

    // we want to copy the contents of the input to the first list element
    //  if it wasn't choosen yet
    connect(suggestionInput, &SuggestionLineEdit::textChanged,
            this, [this](){
                list->addFirst(suggestionInput->text());
                hideable->setInSightFull(true);
            });

    // pressed enter or choosen from suggestion
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

    // if after deletion list has 0 elements hdie it
    connect(list, &ItemList::deleted,
            this, [this](){
                if(list->count() == 0)
                {
                    hideable->setInSightFull(false);
                }
            });

    // set inbetween label width
    connect(list, &ItemList::sizeChanged,
            this, [this](){
                //qDebug() << "list changed" << list->width() << hideable->getLabel()->width();
                setListLabelWidth();
                emit sizeChanged();
            });
    connect(suggestionInput, &SuggestionLineEdit::sizeChanged,
            this, [this](){
                //qDebug() << "suggestion changed" << suggestionInput->width() << hideable->getLabel()->width();
                setListLabelWidth();
                emit sizeChanged();
            });
}

void ListInput::setListLabelWidth()
{
    const int listWidth = list->width();
    const int inputWidth = suggestionInput->width();

    const int max = std::max(listWidth, inputWidth);

    hideable->getLabel()->setFixedWidth(max);
    setFixedWidth(max);
}
