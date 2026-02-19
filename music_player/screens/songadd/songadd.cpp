#include "songadd.h"

//#include <screens/screen/screen.h>
#include <QScrollArea>
#include "widgets/nicefileedit/nicefileedit.h"
#include <QFileInfo>

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
    //NiceLineEdit* plik = addTextField("plik", "plik");
    //QPushButton* selectFile_pb = new QPushButton(this);
    //selectFile_pb->setText("Wybierz plik");
    //addWidget(selectFile_pb);
    NiceFileEdit* file_nfe = new NiceFileEdit("Plik", this);
    addWidget(file_nfe);
    NiceLineEdit* nazwa = addTextField("Nazwa", "Nazwa");
    NiceLineEdit* author = addTextField("autor", "autor");
    QLabel* authors_l = new QLabel(this);
    authors_l->setText("autorzy(68)");
    addWidget(authors_l);
    QScrollArea* authors_sa = new QScrollArea(this);
    addWidget(authors_sa);
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
