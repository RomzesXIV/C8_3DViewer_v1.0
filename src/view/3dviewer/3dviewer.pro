__linux__ {
QT       += core gui opengl widgets
}
macx {
QT       += core gui opengl widgets openglwidgets
}
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../../extLibs/QtGifImage-master/src/3rdParty/giflib/dgif_lib.c \
    ../../extLibs/QtGifImage-master/src/3rdParty/giflib/egif_lib.c \
    ../../extLibs/QtGifImage-master/src/3rdParty/giflib/gif_err.c \
    ../../extLibs/QtGifImage-master/src/3rdParty/giflib/gif_font.c \
    ../../extLibs/QtGifImage-master/src/3rdParty/giflib/gif_hash.c \
    ../../extLibs/QtGifImage-master/src/3rdParty/giflib/gifalloc.c \
    ../../extLibs/QtGifImage-master/src/3rdParty/giflib/quantize.c \
    ../../extLibs/QtGifImage-master/src/gifimage/qgifimage.cpp \
    ../../model/model.c \
    ../../model/model_operations.c \
    ../../model/parser.c \
    main.cpp \
    mainwindow.cpp \
    model_data.cpp \
    settings_widget.cpp \
    viewer.cpp

HEADERS += \
    ../../extLibs/QtGifImage-master/src/3rdParty/giflib/gif_hash.h \
    ../../extLibs/QtGifImage-master/src/3rdParty/giflib/gif_lib.h \
    ../../extLibs/QtGifImage-master/src/3rdParty/giflib/gif_lib_private.h \
    ../../extLibs/QtGifImage-master/src/gifimage/qgifglobal.h \
    ../../extLibs/QtGifImage-master/src/gifimage/qgifimage.h \
    ../../extLibs/QtGifImage-master/src/gifimage/qgifimage_p.h \
    ../../model/model.h \
    ../../model/model_operations.h \
    ../../model/parser.h \
    mainwindow.h \
    model_data.h \
    settings_widget.h \
    viewer.h

FORMS += \
    mainwindow.ui \
    settings_widget.ui

DESTDIR = ~/Viewer
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../../extLibs/QtGifImage-master/src/gifimage/qtgifimage.pri \
    2.fsh \
    22.vsh

RESOURCES += \
    shaders.qrc
