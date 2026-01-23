#ifndef TEST1_H
#define TEST1_H

#include "screens/screen/screen.h"
#include <navigation/appstate.h>
#include <memory>

namespace Ui {
class test1;
}

class test1 : public Screen
{
    Q_OBJECT

public:
    explicit test1(AppState* appState, QWidget *parent = nullptr, std::shared_ptr<void> recreationData = nullptr);
    ~test1() override;

    void changeScreenToTest2();
    void changeScreenToTest3();
    std::string name() override;
    std::shared_ptr<void> recreationData() override;
    void recreate() override;

    void saveEditableState();

private:
    Ui::test1 *ui;
    struct RecreationData
    {
        QString str;
    };
    std::shared_ptr<RecreationData> recreation_data;
};

#endif // TEST1_H
