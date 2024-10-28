QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    othelloai.cpp \
    main.cpp \
    othello.cpp \
    qgamehelpdlg.cpp \
    othelloengine.cpp \
    qothelloview.cpp
    othelloai.cpp

HEADERS += \
    othello.h \
    othelloai.h \
    qgamehelpdlg.h \
    othelloengine.h \
    qothelloview.h
    othelloai.h

FORMS += \
    othello.ui \
    gamehelp.ui

RESOURCES += \
    othello.qrc

CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

TRANSLATIONS += \
    Othello_zh_CN.ts
