#include "test1.h"
#include "ui_test1.h"

#include <screens/screen/screen.h>
#include <memory>

test1::test1(AppState *appState, QWidget *parent, std::shared_ptr<void> recreationData)
    : Screen(parent)
    , ui(new Ui::test1)
{
    if(appState == nullptr)
    {
        qDebug() << "no AppState in " << name();
        return;
    }

    ui->setupUi(this);

    if(recreationData != nullptr)
    {
        recreation_data = std::static_pointer_cast<RecreationData>(recreationData);
        recreate();
    }
    else
    {
        recreation_data = std::make_shared<RecreationData>();
    }



    connect(ui->screen2_pb, &QPushButton::clicked, this, &test1::changeScreenToTest2);
    connect(ui->screen3_pb, &QPushButton::clicked, this, &test1::changeScreenToTest3);
    connect(ui->back_pb, &QPushButton::clicked, this, &Screen::back);

    //connect(ui->editable_le, &QLineEdit::textChanged, this, &test1::saveEditableState);

    qDebug() << name() << appState << " " << recreationData.get();
}

test1::~test1()
{
    delete ui;
}

void test1::changeScreenToTest2()
{
    emit changeScreenTo(Screens::test2);
}

void test1::changeScreenToTest3()
{
    emit changeScreenTo(Screens::test3);
}

std::string test1::name()
{
    return "test1";
}

std::shared_ptr<void> test1::recreationData()
{
    std::shared_ptr<void> vptr = recreation_data;
    return vptr;
}

void test1::recreate()
{
    qDebug() << "recreating " << name();
    RecreationData* rd = recreation_data.get();
    ui->editable_le->setText(rd->str);
}

void test1::saveEditableState()
{
    RecreationData* rd = recreation_data.get();
    rd->str = ui->editable_le->text();

}
