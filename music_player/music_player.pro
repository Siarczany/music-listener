QT       += core gui
QT += sql
QT += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    navigation/appstate.cpp \
    navigation/navigation.cpp \
    screens/screen/screen.cpp \
    screens/test1/test1.cpp \
    screens/test2/test2.cpp \
    screens/test3/test3.cpp \

HEADERS += \
    navigation/filo.h \
    navigation/filoimpl.h \
    navigation/appstate.h \
    navigation/navigation.h \
    screens/screen/screen.h \
    screens/screens.h \
    screens/test1/test1.h \
    screens/test2/test2.h \
    screens/test3/test3.h \


FORMS += \
    screens/test1/test1.ui \
    screens/test2/test2.ui \
    screens/test3/test3.ui \



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
