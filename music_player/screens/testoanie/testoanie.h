#ifndef TESTOANIE_H
#define TESTOANIE_H

#include <screens/screen/screen.h>
#include <navigation/appstate.h>
#include <memory>

class testoanie : public Screen
{
    Q_OBJECT

public:
    explicit testoanie(AppState* appState, QWidget *parent = nullptr, std::shared_ptr<void> recreationData = nullptr);
    ~testoanie() override;

    std::string name() override;
    std::shared_ptr<void> recreationData() override;
    void recreate() override;

    //* // setup widgets
    //setupEditable();
    //*/


    //* // state save
    //void saveEditableState();
    //*/


    //* // navigation
    //void changeScreenToOtherScreen();
    //*/

private:
    //Ui::Template *ui;
    struct RecreationData
    {
        int editableValue;
    };
    std::shared_ptr<RecreationData> recreation_data;
};

#endif // TEST1_H
