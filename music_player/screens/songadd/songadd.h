#ifndef SONGADD_H
#define SONGADD_H

#include <screens/screen/form.h>
#include <navigation/appstate.h>
#include <memory>

class SongAdd : public Form
{
    Q_OBJECT

public:
    explicit SongAdd(AppState* appState, QWidget *parent = nullptr, std::shared_ptr<void> recreationData = nullptr);
    ~SongAdd() override;

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
    struct RecreationData
    {
        int editableValue;
    };
    std::shared_ptr<RecreationData> recreation_data;

    QStringList querytest(const QString& text);
};

#endif // SONGADD_H
