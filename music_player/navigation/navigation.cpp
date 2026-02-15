#include "navigation.h"
#include <screens/test1/test1.h>
#include <screens/test2/test2.h>
#include <screens/test3/test3.h>
#include "screens/testoanie/testoanie.h"
#include <screens/login/login.h>

Screen *Navigation::createScreen(Screens lookup, std::shared_ptr<void> recreationData)
{
    Screen* newScreen = nullptr;
    switch(lookup)
    {
        case Screens::test1:
        {
            newScreen = new test1(&appState, this, recreationData);
            break;
        }
        case Screens::test2:
        {
            newScreen = new test2(&appState, this, recreationData);
            break;
        }
        case Screens::test3:
        {
            newScreen = new test3(&appState, this, recreationData);
            break;
        }
        case Screens::testoanie:
        {
            newScreen = new testoanie(&appState, this, recreationData);
            break;
        }
        case Screens::Login:
        {
            newScreen = new Login(&appState, this, recreationData);
            break;
        }
        default:
        {
            return nullptr;
        }
    }
    connect(newScreen, &Screen::changeScreenTo, this, &Navigation::changeScreenTo);
    connect(newScreen, &Screen::back, this, &Navigation::back);

    return  newScreen;
}

Navigation::Navigation(Screens firstScreen, QWidget *parent)
    : QMainWindow(parent)
{
    //appState.setDatabase();
    setScreenTo(firstScreen);
}

Navigation::~Navigation()
{
    if(currentScreenPtr != nullptr)
    {
        delete currentScreenPtr;
    }
    if(previousScreenPtr != nullptr)
    {
        delete previousScreenPtr;
    }
}



void Navigation::setScreenTo(Screens lookup, std::shared_ptr<void> recreationData)
{
    previousScreenPtr = currentScreenPtr;
    currentScreenPtr = createScreen(lookup, recreationData);
    setCentralWidget(currentScreenPtr);

    if(previousScreenPtr != nullptr)
    {
        delete previousScreenPtr;
        previousScreenPtr = nullptr;
    }

    currentScreen = lookup;

    qDebug() << "current screen is: " << currentScreenPtr->name() << "\n";
}

void Navigation::changeScreenTo(Screens lookup)
{

    PreviousScreen previousScreen;
    previousScreen.screen = currentScreen;
    previousScreen.recreationData = currentScreenPtr->recreationData();

    previousScreens.add(previousScreen);

    setScreenTo(lookup, nullptr);
}

void Navigation::back()
{
    PreviousScreen previousScreen = previousScreens.get();

    setScreenTo(previousScreen.screen, previousScreen.recreationData);
}
