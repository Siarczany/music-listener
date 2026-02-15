#include "testoanie.h"

#include <screens/screen/screen.h>
//#include "widgets/nicelineedit/resizablelineedit.h"

testoanie::testoanie(AppState *appState, QWidget *parent, std::shared_ptr<void> recreationData)
    : Screen(parent)
{
    if(appState == nullptr)
    {
        qDebug() << "no AppState in " << testoanie::name();
        return;
    }

    //* // data needed by the screen
    //this->db = appState->database();
    //*/

    //ui->setupUi(this);

    /* // widgets setups
    setupWidget1();
    setupWidget2();
    setupWIdget3();
    //*/

    if(recreationData != nullptr)
    {
        recreation_data = std::static_pointer_cast<RecreationData>(recreationData);
        testoanie::recreate();
    }
    else
    {
        recreation_data = std::make_shared<RecreationData>();
    }

    //* // navigation to other screens
    //connect(ui->toScreen2_pb, &QPushButton::clicked, this, &SomeScreen::changeScreenToScreen2);
    //connect(ui->back_pb, &QPushButton::clicked, this, Screen::back);
    //*/

    qDebug() << testoanie::name() << appState << " " << recreationData.get();
}

testoanie::~testoanie()
{
    //delete ui;
    qDebug() << "hello";
}

std::string testoanie::name()
{
    return "testoanie";
}

std::shared_ptr<void> testoanie::recreationData()
{
    std::shared_ptr<void> vptr = recreation_data;
    return vptr;
}

void testoanie::recreate()
{
    qDebug() << "recreating " << testoanie::name();
    //RecreationData* rd = recreation_data.get();
}
