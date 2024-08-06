#-------------------------------------------------
#
# Project created by QtCreator 2024-07-17T16:02:03
#
#-------------------------------------------------

QT       += core gui
QT       += core gui multimedia multimediawidgets widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtdemo3
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11
CONFIG+=resources_big

SOURCES += \
        main.cpp \
    util/sqliteutil.cpp \
    view/loginwidget.cpp \
    view/mainwidget.cpp \
    view/myview.cpp \
    view/regwidget.cpp \
    controller/usercontroller.cpp \
    controller/videocontroller.cpp \
    service/video.cpp \
    service/bunner.cpp \
    service/myitem.cpp \
    service/usermodel.cpp \
    util/verifycode.cpp \
    view/videoplayer.cpp \
    service/channel.cpp \
    controller/channelcontroller.cpp \
    service/channelmodel.cpp \
    service/userinfo.cpp \
    controller/maincontroller.cpp

HEADERS += \
    util/sqliteutil.h \
    view/loginwidget.h \
    view/mainwidget.h \
    view/myview.h \
    view/regwidget.h \
    service/usermodel.h \
    controller/usercontroller.h \
    controller/videocontroller.h \
    service/video.h \
    service/bunner.h \
    service/myitem.h \
    util/verifycode.h \
    view/videoplayer.h \
    service/channel.h \
    controller/channelcontroller.h \
    service/channelmodel.h \
    service/userinfo.h \
    controller/maincontroller.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
DESTDIR+=bin
#配置库文件路径（api路径）
LIBS+=$$PWD/lib/sqlite3.lib

