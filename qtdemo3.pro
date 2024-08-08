#-------------------------------------------------
#
# Project created by QtCreator 2024-07-17T16:02:03
#
#-------------------------------------------------

QT       += core gui
QT       += core gui multimedia multimediawidgets widgets
QT       += sql
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

include(tests/test_Qtdemo3.pro)

SOURCES += \
        main.cpp \
    util/sqliteutil.cpp \
    view/loginwidget.cpp \
    view/mainwidget.cpp \
    view/myview.cpp \
    view/regwidget.cpp \
    controller/usercontroller.cpp \
    controller/videocontroller.cpp \
    entity/video.cpp \
    entity/bunner.cpp \
    service/myitem.cpp \
    service/usermodel.cpp \
    util/verifycode.cpp \
    view/videoplayer.cpp \
    entity/channel.cpp \
    controller/channelcontroller.cpp \
    service/channelmodel.cpp \
    entity/userinfo.cpp \
    controller/maincontroller.cpp \
    controller/videoservice.cpp \
    view/mainscreen.cpp \
    util/ffmpegdecoder.cpp

HEADERS += \
    util/sqliteutil.h \
    view/loginwidget.h \
    view/mainwidget.h \
    view/myview.h \
    view/regwidget.h \
    service/usermodel.h \
    controller/usercontroller.h \
    controller/videocontroller.h \
    entity/video.h \
    entity/bunner.h \
    service/myitem.h \
    util/verifycode.h \
    view/videoplayer.h \
    entity/channel.h \
    controller/channelcontroller.h \
    service/channelmodel.h \
    entity/userinfo.h \
    controller/maincontroller.h \
    controller/videoservice.h \
    view/mainscreen.h \
    util/ffmpegdecoder.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

LIBS +=$$PWD/ffmpeglib/lib/avcodec.lib \
        $$PWD/ffmpeglib/lib/avdevice.lib \
        $$PWD/ffmpeglib/lib/avfilter.lib \
        $$PWD/ffmpeglib/lib/avformat.lib \
        $$PWD/ffmpeglib/lib/avutil.lib \
        $$PWD/ffmpeglib/lib/swresample.lib \
        $$PWD/ffmpeglib/lib/swscale.lib \

INCLUDEPATH += $$PWD/ffmpeglib/include      #头文件路径
RESOURCES += \
    resource.qrc
DESTDIR+=bin
#配置库文件路径（api路径）
LIBS+=$$PWD/lib/sqlite3.lib

FORMS += \
    view/mainscreen.ui

