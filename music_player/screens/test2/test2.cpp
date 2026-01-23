#include "test2.h"
#include "ui_test2.h"

#include <screens/screen/screen.h>

test2::test2(AppState *appState, QWidget *parent, std::shared_ptr<void> recreationData)
    : Screen(parent)
    , ui(new Ui::test2)
{
    if(appState == nullptr)
    {
        qDebug() << "no AppState in " << name();
        return;
    }

    ui->setupUi(this);
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

    connect(ui->toScreen1_pb, &QPushButton::clicked, this, &test2::changeScreenToTest1);
    connect(ui->toScreen3_pb, &QPushButton::clicked, this, &test2::changeScreenToTest3);
    connect(ui->back_pb, &QPushButton::clicked, this, back);



    qDebug() << name() << appState << " " << recreationData.get();
}

test2::~test2()
{
    delete ui;
}

void test2::changeScreenToTest1()
{
    emit changeScreenTo(Screens::test1);
}

void test2::changeScreenToTest3()
{
    emit changeScreenTo(Screens::test3);
}

std::string test2::name()
{
    return "test2";
}

std::shared_ptr<void> test2::recreationData()
{
    std::shared_ptr<void> vptr = recreation_data;
    return vptr;
}

void test2::recreate()
{
    qDebug() << "recreating " << name();
    RecreationData* rd = recreation_data.get();
    ui->editable_hs->setValue(rd->value);
}

void test2::saveEditableState()
{
    RecreationData* rd = recreation_data.get();
    rd->value = ui->editable_hs->value();
}

void test2::setupEditable()
{
    ui->editable_hs->setMinimum(100);
    ui->editable_hs->setMaximum(125);

    connect(ui->editable_hs, &QSlider::valueChanged, this, &test2::saveEditableState);
}
