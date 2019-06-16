#//////////////////////////////////////////
# тестовая работа 2 часть к занятию https://youtu.be/Ww-aoNC8VQU
#//////////////////////////////////////////

QT       += core gui widgets

TARGET = ogltest2-2
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++17

SOURCES += \
        main.cpp \
        oglwidget.cpp \
        simpleobject3d.cpp

HEADERS += \
        oglwidget.h \
        simpleobject3d.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    shaders.qrc \
    textures.qrc
