#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <QMainWindow>
#include "appstate.h"
#include "filo.h"
#include <screens/screen/screen.h>
#include <screens/screens.h>
#include <memory>

class Navigation : public QMainWindow
{
    Q_OBJECT
private:
    struct PreviousScreen
    {
        Screens screen;
        std::shared_ptr<void> recreationData;
    };
    filo<PreviousScreen> previousScreens;
    Screens currentScreen;
    Screen* currentScreenPtr = nullptr;
    Screen* previousScreenPtr = nullptr;
    AppState appState;

    Screen* createScreen(Screens lookup, std::shared_ptr<void> recreationData = nullptr);

    void setScreenTo(Screens lookup, std::shared_ptr<void> recreationData = nullptr);
public:
    Navigation(Screens firstScreen, QWidget *parent = nullptr);
    ~Navigation();

    void changeScreenTo(Screens lookup);
    void back();

};


#endif // NAVIGATION_H
