#include "test3.h"
#include "ui_test3.h"

#include <screens/screen/screen.h>

test3::test3(AppState *appState, QWidget *parent, std::shared_ptr<void> recreationData)
    : Screen(parent)
    , ui(new Ui::test3)
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
    setupEditable();

    if(recreationData != nullptr)
    {
        recreation_data = std::static_pointer_cast<RecreationData>(recreationData);
        recreate();
    }
    else
    {
        recreation_data = std::make_shared<RecreationData>();
    }

    connect(ui->toScreen1_pb, &QPushButton::clicked, this, &test3::changeScreenToTest1);
    connect(ui->toScreen2_pb, &QPushButton::clicked, this, &test3::changeScreenToTest2);
    connect(ui->back_pb, &QPushButton::clicked, this, Screen::back);
    //* // navigation to other screens
    //connect(ui->toScreen2_pb, &QPushButton::clicked, this, &SomeScreen::changeScreenToScreen2);
    //connect(ui->back_pb, &QPushButton::clicked, this, Screen::back);
    //*/

    qDebug() << name() << appState << " " << recreationData.get();
}

test3::~test3()
{
    delete ui;
}

void test3::changeScreenToTest1()
{
    emit changeScreenTo(Screens::test1);
}

void test3::changeScreenToTest2()
{
    emit changeScreenTo(Screens::test2);
}

std::string test3::name()
{
    return "test3";
}

std::shared_ptr<void> test3::recreationData()
{
    std::shared_ptr<void> vptr = recreation_data;
    return vptr;
}

void test3::recreate()
{
    qDebug() << "recreating " << name();
    RecreationData* rd = recreation_data.get();
    ui->editable_sb->setValue(rd->value);
}

void test3::setupEditable()
{
    ui->editable_sb->setMinimum(1024);
    ui->editable_sb->setMaximum(2048);

    connect(ui->editable_sb, &QSpinBox::valueChanged, this, &test3::saveEditableState);
}

void test3::saveEditableState()
{
    RecreationData* rd = recreation_data.get();
    rd->value = ui->editable_sb->value();
}
