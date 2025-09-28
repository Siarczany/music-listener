QT       += core gui
QT += sql
QT += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    editscreen.cpp \
    login_screen.cpp \
    main.cpp \
    mainwindow.cpp \
    player_screen.cpp \
    playlist_add_screen.cpp \
    playlist_edit_screen.cpp \
    playlist_song_add_screen.cpp \
    playlist_song_edit_screen.cpp \
    playlists_screen.cpp \
    playlists_screen_slider.cpp \
    register_screen.cpp \
    songs_add_screen.cpp \
    songs_edit_screen.cpp \
    songs_screen.cpp \
    songs_tag_add_screen.cpp \
    songs_tag_screen.cpp \
    testowanie.cpp \
    texts.cpp \
    widgets/NiceColumns/internal/column.cpp \
    widgets/NiceColumns/internal/dragwidget.cpp \
    widgets/NiceColumns/internal/headeroptions.cpp \
    widgets/NiceColumns/internal/rowoptions.cpp \
    widgets/NiceColumns/nicecolumns.cpp \
    widgets/elidedlabel.cpp \
    widgets/playlistlabel.cpp \
    widgets/suggestionlineedit.cpp \
    widgets/triplecheckbox.cpp

HEADERS += \
    editscreen.h \
    login_screen.h \
    mainwindow.h \
    player_screen.h \
    playlist_add_screen.h \
    playlist_edit_screen.h \
    playlist_song_add_screen.h \
    playlist_song_edit_screen.h \
    playlists_screen.h \
    playlists_screen_slider.h \
    register_screen.h \
    sizes.h \
    songs_add_screen.h \
    songs_edit_screen.h \
    songs_screen.h \
    songs_tag_add_screen.h \
    songs_tag_screen.h \
    testowanie.h \
    texts.h \
    widgets/NiceColumns/internal/column.h \
    widgets/NiceColumns/internal/dragwidget.h \
    widgets/NiceColumns/internal/headeroptions.h \
    widgets/NiceColumns/internal/rowoptions.h \
    widgets/NiceColumns/nicecolumns.h \
    widgets/elidedlabel.h \
    widgets/playlistlabel.h \
    widgets/suggestionlineedit.h \
    widgets/triplecheckbox.h

FORMS += \
    login_screen.ui \
    mainwindow.ui \
    player_screen.ui \
    playlist_add_screen.ui \
    playlist_edit_screen.ui \
    playlist_song_add_screen.ui \
    playlist_song_edit_screen.ui \
    playlists_screen.ui \
    register_screen.ui \
    songs_add_screen.ui \
    songs_edit_screen.ui \
    songs_screen.ui \
    songs_tag_add_screen.ui \
    songs_tag_screen.ui \
    testowanie.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    triple_check_box.qrc
