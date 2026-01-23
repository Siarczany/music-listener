#include "Template.h"
#include "ui_Template.h"

#include <screens/screen/screen.h>

Template::Template(AppState *appState, QWidget *parent, std::shared_ptr<void> recreationData)
    : Screen(parent)
    , ui(new Ui::Template)
{
    if(appState == nullptr)
    {
        qDebug() << "no AppState in " << name();
        return;
    }

    //* // data needed by the screen
    //this->db = appState->database();
    //*/

    ui->setupUi(this);

    /* // widgets setups
    setupWidget1();
    setupWidget2();
    setupWIdget3();
    //*/

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

Template::~Template()
{
    delete ui;
}

std::string Template::name()
{
    return "test3";
}

std::shared_ptr<void> Template::recreationData()
{
    std::shared_ptr<void> vptr = recreation_data;
    return vptr;
}

void Template::recreate()
{
    qDebug() << "recreating " << name();
    RecreationData* rd = recreation_data.get();
    ui->editable_sb->setValue(rd->value);
}
