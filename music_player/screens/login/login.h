#ifndef LOGIN_H
#define LOGIN_H

#include <screens/screen/form.h>
#include <navigation/appstate.h>
#include <memory>


class Login : public Form
{
    Q_OBJECT

public:
    explicit Login(AppState* appState, QWidget *parent = nullptr, std::shared_ptr<void> recreationData = nullptr);
    ~Login() override;

    std::string name() override;
    std::shared_ptr<void> recreationData() override;
    void recreate() override;

private:
    struct RecreationData
    {
    };
    std::shared_ptr<RecreationData> recreation_data;
};

#endif // LOGIN_H
