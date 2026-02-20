QT       += core gui
QT += sql
QT += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets-private

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    navigation/appstate.cpp \
    navigation/navigation.cpp \
    screens/screen/screen.cpp \
    screens/screen/form.cpp \
    screens/test1/test1.cpp \
    screens/test2/test2.cpp \
    screens/test3/test3.cpp \
    screens/testoanie/testoanie.cpp \
    screens/login/login.cpp \
    widgets/nicelineedit/nicelineedit.cpp \
    widgets/nicelineedit/resizablelineedit.cpp \
    widgets/nicelineedit/dragwidget.cpp \
    widgets/nicelineedit/scrollablelabel.cpp \
    screens/songadd/songadd.cpp \
    widgets/nicefileedit/nicefileedit.cpp \
    widgets/nicelineedit/scrollablelineedit.cpp \ #possible delete because idk how to make it work as I wawnt it to
    widgets/suggestionlinedit/suggestionlineedit.cpp \
    widgets/suggestionlinedit/suggestionpopup.cpp \


HEADERS += \
    navigation/filo.h \
    navigation/filoimpl.h \
    navigation/appstate.h \
    navigation/navigation.h \
    screens/screen/screen.h \
    screens/screen/form.h \
    screens/screens.h \
    screens/test1/test1.h \
    screens/test2/test2.h \
    screens/test3/test3.h \
    screens/testoanie/testoanie.h \
    screens/login/login.h \
    widgets/nicelineedit/nicelineedit.h \
    widgets/nicelineedit/resizablelineedit.h \
    widgets/nicelineedit/dragwidget.h \
    widgets/nicelineedit/scrollablelabel.h \
    screens/songadd/songadd.h \
    widgets/nicefileedit/nicefileedit.h \
    widgets/nicelineedit/scrollablelineedit.h \ # possible delete explaination up
    widgets/suggestionlinedit/suggestionlineedit.h \
    widgets/suggestionlinedit/suggestionpopup.h \

FORMS += \
    screens/test1/test1.ui \
    screens/test2/test2.ui \
    screens/test3/test3.ui \



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
