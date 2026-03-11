#include "songadd.h"

//#include <screens/screen/screen.h>
#include <QScrollArea>
#include "widgets/nicefileedit/nicefileedit.h"
#include <QFileInfo>
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

    ListInput* li = new ListInput(this);
    li->setInputLabel("Autor");
    li->setListLabel("Autorzy");
    li->setQuery([this](const QString& text){
        QStringList all;
        all << "asd" << "sdf" << "dfg" << "fgh" << "ghj" << "hjk" << "jkl";

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
    li->setInSight(false);
    addWidget(li);

    addBackButton();

    connect(file_nfe, &NiceFileEdit::textChanged, this, [nazwa](const QString& text){
        QFileInfo file(text);
        nazwa->setText(file.baseName());
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
