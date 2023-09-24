QT       += core gui opengl

macx {
    QT += openglwidgets
}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ima/giflib/dgif_lib.c \
    ima/giflib/egif_lib.c \
    ima/giflib/gif_err.c \
    ima/giflib/gif_font.c \
    ima/giflib/gif_hash.c \
    ima/giflib/gifalloc.c \
    ima/giflib/quantize.c \
    ima/qgifimage.cpp \
    main.cpp \
    mainwindow.cpp \
    mywidget.cpp \
    ../parser.c \
    ../affine.c \


HEADERS += \
    ima/giflib/gif_hash.h \
    ima/giflib/gif_lib.h \
    ima/giflib/gif_lib_private.h \
    ima/qgifglobal.h \
    ima/qgifimage.h \
    ima/qgifimage_p.h \
    mainwindow.h \
    mywidget.h \
    ../3dview.h

SUBDIRS += \
  ima/gifimage.pro


FORMS += \
    mainwindow.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
