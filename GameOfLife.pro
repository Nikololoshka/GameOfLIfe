QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GameOfLife
TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

SOURCES += \
        main.cpp \
    cell.cpp \
    gameOfLifeWindow.cpp \
    classicRules.cpp \
    customMazeRules.cpp \
    customRules.cpp \
    customCell.cpp

HEADERS += \
    cell.h \
    gameOfLifeWindow.h \
    classicRules.h \
    customMazeRules.h \
    customRules.h \
    customCell.h

FORMS += \
        gameOfLifeWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
