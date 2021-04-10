QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    tilemap.cpp \
    tilemapbuilder.cpp

HEADERS += \
    tilemap.h \
    tilemapbuilder.h

FORMS += \
    tilemap.ui

TARGET = "Tilemap Viewer"
QMAKE_TARGET_DESCRIPTION = "Tilemap Viewer"

RC_ICONS = icon.ico

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


win32: LIBS += -L$$PWD/3rdparty/ImageMagick/lib/ -lCORE_RL_Magick++_ -lCORE_RL_MagickCore_ -lCORE_RL_MagickWand_

INCLUDEPATH += $$PWD/3rdparty/ImageMagick/include
INCLUDEPATH += $$PWD/3rdparty/ImageMagick/include/Magick++
INCLUDEPATH += $$PWD/3rdparty/ImageMagick/include/MagickCore
INCLUDEPATH += $$PWD/3rdparty/ImageMagick/include/MagickWand

DEPENDPATH += $$PWD/3rdparty/ImageMagick/include

DEFINES += "MAGICKCORE_QUANTUM_DEPTH=16"
DEFINES += "MAGICKCORE_HDRI_ENABLE=1"

