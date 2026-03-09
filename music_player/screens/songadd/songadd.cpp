#include "songadd.h"

//#include <screens/screen/screen.h>
#include <QScrollArea>
#include "widgets/nicefileedit/nicefileedit.h"
#include <QFileInfo>
#include "authors.h"
#include "widgets/listinput/listinput.h"

SongAdd::SongAdd(AppState *appState, QWidget *parent, std::shared_ptr<void> recreationData)
    : Form(parent)
{
    if(appState == nullptr)
    {
        qDebug() << "no AppState in " << name();
        return;
    }

    //* // data needed by the screen
    //this->db = appState->database();
    //*/

    // widgets setups
    NiceFileEdit* file_nfe = new NiceFileEdit("Plik", this);
    addWidget(file_nfe);
    NiceLineEdit* nazwa = addTextField("Nazwa", "Nazwa");

    NiceLineEdit* author = new NiceLineEdit("Autor", this, NiceLineEdit::LineEdit::Suggestion);
    addWidget(author);

    SuggestionLineEdit* suggestionAuthor = static_cast<SuggestionLineEdit*>(author->getLineEdit());
    suggestionAuthor->setQuery([this](const QString& text){
        QStringList all;
        all << "qwe" << "wer" << "ert" << "rty" << "tyu" << "yui" << " uio" << "iop" << "qe";

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

    AuthorsList* al = new AuthorsList(this);
    HideableWidget* he = new HideableWidget(al, al->getHiddenWidget(), this);
    he->setText("Autorzy");
    he->setInSight(false);
    addWidget(he);

    ListInput* li = new ListInput(this);
    addWidget(li);

    addBackButton();

    connect(suggestionAuthor, &SuggestionLineEdit::textChanged,
            this, [suggestionAuthor, al](){
        al->addFirst(suggestionAuthor->text());
    });
    connect(suggestionAuthor, &SuggestionLineEdit::choosen,
            this, [suggestionAuthor, al](){
        al->add(suggestionAuthor->text());
        suggestionAuthor->clear();
    });
    connect(suggestionAuthor, &SuggestionLineEdit::returnPressed,
            this, [suggestionAuthor, al](){
        qDebug() << "enter";
        al->add(suggestionAuthor->text());
        suggestionAuthor->clear();
    });

    connect(file_nfe, &NiceFileEdit::textChanged, this, [nazwa](const QString& text){
        QFileInfo file(text);
        nazwa->setText(file.baseName());

    });

    connect(suggestionAuthor, &SuggestionLineEdit::choosen,
            this, [author](){
        qDebug() << "choosen" << author->text();
    });

    if(recreationData != nullptr)
    {
        recreation_data = std::static_pointer_cast<RecreationData>(recreationData);
        recreate();
    }
    else
    {
        recreation_data = std::make_shared<RecreationData>();
    }

    //* // navigation to other screens
    //connect(ui->toScreen2_pb, &QPushButton::clicked, this, &SomeScreen::changeScreenToScreen2);
    //connect(ui->back_pb, &QPushButton::clicked, this, Screen::back);
    //*/

    qDebug() << name() << appState << " " << recreationData.get();
}

SongAdd::~SongAdd()
{
}

std::string SongAdd::name()
{
    return "test3";
}

std::shared_ptr<void> SongAdd::recreationData()
{
    std::shared_ptr<void> vptr = recreation_data;
    return vptr;
}

void SongAdd::recreate()
{
    qDebug() << "recreating " << name();
    //RecreationData* rd = recreation_data.get();
}
