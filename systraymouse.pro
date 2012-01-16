#-------------------------------------------------
#
# Project created by QtCreator 2012-01-13T13:12:57
#
#-------------------------------------------------

QT       += core gui

TARGET = systraymouse
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    device.cpp

HEADERS  += mainwindow.h \
    device.h
LIBS +=-lusb-1.0
FORMS    += mainwindow.ui

RESOURCES     = systraymouse.qrc \
    systraymouse.qrc
QT           += xml svg

# install
target.path = $$[QT_INSTALL_EXAMPLES]/desktop/systraymouse
sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS systraymouse.pro resources images
sources.path = $$[QT_INSTALL_EXAMPLES]/desktop/systraymouse
INSTALLS += target sources


wince* {
        CONFIG(debug, release|debug) {
                addPlugins.sources = $$QT_BUILD_TREE/plugins/imageformats/qsvgd4.dll
        }
        CONFIG(release, release|debug) {
                addPlugins.sources = $$QT_BUILD_TREE/plugins/imageformats/qsvg4.dll
        }
        addPlugins.path = imageformats
        DEPLOYMENT += addPlugins
}
