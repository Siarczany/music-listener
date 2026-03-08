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
    screens/songadd/authors.cpp \
    screens/test1/test1.cpp \
    screens/test2/test2.cpp \
    screens/test3/test3.cpp \
    screens/testoanie/testoanie.cpp \
    screens/login/login.cpp \
    widgets/hideablewidget/clickablelabel.cpp \
    widgets/hideablewidget/hiddenwidget.cpp \
    widgets/hideablewidget/hideablewidget.cpp \
    widgets/nicelineedit/nicelineedit.cpp \
    screens/songadd/songadd.cpp \
    widgets/nicefileedit/nicefileedit.cpp \
    widgets/nicelineedit/mylineedit/mylineedit.cpp \
    widgets/nicelineedit/suggestionlinedit/suggestionlineedit.cpp \
    widgets/nicelineedit/suggestionlinedit/suggestionpopup.cpp \
    widgets/resizablewidget/dragwidget.cpp \
    widgets/resizablewidget/resizeablewidget.cpp \
    widgets/scrollablelabel/scrollablelabel.cpp \
    widgets/listinput/listinput.cpp \
    widgets/viewbase/item.cpp \
    widgets/viewbase/model.cpp \
    widgets/viewbase/mylistwidget.cpp \
    widgets/viewbase/viewbase.cpp


HEADERS += \
    navigation/filo.h \
    navigation/filoimpl.h \
    navigation/appstate.h \
    navigation/navigation.h \
    screens/screen/screen.h \
    screens/screen/form.h \
    screens/screens.h \
    screens/songadd/authors.h \
    screens/test1/test1.h \
    screens/test2/test2.h \
    screens/test3/test3.h \
    screens/testoanie/testoanie.h \
    screens/login/login.h \
    widgets/hideablewidget/clickablelabel.h \
    widgets/hideablewidget/hiddenwidget.h \
    widgets/hideablewidget/hideablewidget.h \
    widgets/nicelineedit/nicelineedit.h \
    screens/songadd/songadd.h \
    widgets/nicefileedit/nicefileedit.h \
    widgets/nicelineedit/mylineedit/mylineedit.h \
    widgets/nicelineedit/suggestionlinedit/suggestionlineedit.h \
    widgets/nicelineedit/suggestionlinedit/suggestionpopup.h \
    widgets/resizablewidget/dragwidget.h \
    widgets/resizablewidget/resizeablewidget.h \
    widgets/scrollablelabel/scrollablelabel.h \
    widgets/listinput/listinput.h \
    widgets/viewbase/item.h \
    widgets/viewbase/model.h \
    widgets/viewbase/mylistwidget.h \
    widgets/viewbase/viewbase.h

FORMS += \
    screens/test1/test1.ui \
    screens/test2/test2.ui \
    screens/test3/test3.ui \



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
