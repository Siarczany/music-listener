#ifndef SCREEN_H
#define SCREEN_H

#include <QWidget>
#include <navigation/appstate.h>
#include <screens/screens.h>

class Screen : public QWidget
{
    Q_OBJECT

public:
    Screen(QWidget* parent);
    virtual std::string name() = 0;
    virtual std::shared_ptr<void> recreationData() = 0;
    virtual void recreate() = 0; // maybe a bool so that we can create a default if something goes wrong?

    virtual ~Screen() = default;


signals:
    void back();
    void changeScreenTo(Screens screen);

};

#endif // SCREEN_H
