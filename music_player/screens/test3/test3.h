#ifndef TEST3_H
#define TEST3_H

#include "screens/screen/screen.h"
#include <navigation/appstate.h>
#include <memory>

namespace Ui {
class test3;
}

class test3 : public Screen
{
    Q_OBJECT

public:
    explicit test3(AppState* appState, QWidget *parent = nullptr, std::shared_ptr<void> recreationData = nullptr);
    ~test3() override;

    std::string name() override;
    std::shared_ptr<void> recreationData() override;
    void recreate() override;

    //* // setup widgets
    //setupEditable();
    //*/
    void setupEditable();


    //* // state save
    //void saveEditableState();
    //*/
    void saveEditableState();


    //* // navigation
    //void changeScreenToOtherScreen();
    //*/
    void changeScreenToTest1();
    void changeScreenToTest2();

private:
    Ui::test3 *ui;
    struct RecreationData
    {
        int value;
    };
    std::shared_ptr<RecreationData> recreation_data;
};

#endif // TEST1_H
