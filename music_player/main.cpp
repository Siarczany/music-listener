#include <navigation/navigation.h>
#include <screens/screens.h>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Navigation nav(Screens::SongAdd);
    nav.show();
    return a.exec();
}
