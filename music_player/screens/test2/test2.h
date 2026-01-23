#ifndef TEST2_H
#define TEST2_H

#include "screens/screen/screen.h"
#include <navigation/appstate.h>
#include <memory>

namespace Ui {
class test2;
}

class test2 : public Screen
{
    Q_OBJECT

public:
    explicit test2(AppState* appState, QWidget *parent = nullptr, std::shared_ptr<void> recreationData = nullptr);
    ~test2() override;

    void changeScreenToTest1();
    void changeScreenToTest3();
    std::string name() override;
    std::shared_ptr<void> recreationData() override;
    void recreate() override;

    void saveEditableState();
    void setupEditable();

private:
    Ui::test2 *ui;
    struct RecreationData
    {
        int value;
    };
    std::shared_ptr<RecreationData> recreation_data;
};

#endif // TEST2_H
