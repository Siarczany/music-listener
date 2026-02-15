#include "login.h"

#include <screens/screen/screen.h>

class base : public QWidget
{
public:
    base()
    {}
    virtual std::string name() = 0;
};

class derived : public base
{
public:
    explicit derived()
    {
        qDebug() << name();
        // fixes for this stupid ass warning from clang or some shit

        // NOLINTNEXTLINE(clang-analyzer-optin.cplusplus.VirtualCall)
        qDebug() << name();

        qDebug() << derived::name();

        // the analyzer is stupid and sees the virtual function, and goes straight to a most basic implementation which is virtual... xd
        // the compiler is a gigachad and actually thinks and sees that this makes sense so doesn't complain like a baby
        // I think at least, idk compilers and whatever clang is
    }
    std::string name() override
    {
        return "derived";
    }
};

#include "widgets/nicelineedit/resizablelineedit.h"
#include "widgets/nicelineedit/scrollablelabel.h"

Login::Login(AppState *appState, QWidget *parent, std::shared_ptr<void> recreationData)
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


    /* // widgets setups
    setupWidget1();
    setupWidget2();
    setupWIdget3();
    //*/
    addTextField("login", "Login");
    addTextField("Passwword", "pass");
    //ResizableLineEdit* rle = new ResizableLineEdit(this);
    //addWidget(rle);
    NiceLineEdit* nle = new NiceLineEdit("Some start textiiiiiiasddsaDDDDsddsaiiiiiqertyuiopasdfghjklzxcvbnmmnbvcxzlkjhgfdsapoiuytreqiiiiiMmMm this is endys", this);
    addWidget(nle);
    QPushButton* back_pb = addBackButton();
    QPushButton* test_pb = new QPushButton(this);
    test_pb->setText("test");
    addWidget(test_pb);

    connect(test_pb, &QPushButton::clicked, this, [nle]()
            {
        qDebug() << nle->text();
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

    connect(back_pb, &QPushButton::clicked, this, &Login::back);

    qDebug() << name() << appState << " " << recreationData.get();
}

Login::~Login()
{

}

std::string Login::name()
{
    return "login";
}

std::shared_ptr<void> Login::recreationData()
{
    std::shared_ptr<void> vptr = recreation_data;
    return vptr;
}

void Login::recreate()
{
    qDebug() << "recreating " << name();
   // RecreationData* rd = recreation_data.get();
}
