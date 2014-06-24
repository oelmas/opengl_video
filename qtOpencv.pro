#-------------------------------------------------
#
# Project created by QtCreator 2014-06-16T10:51:07
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtOpencv
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    meglwidget.cpp

HEADERS  += mainwindow.h \
    meglwidget.h

FORMS    += mainwindow.ui

unix:!macx: LIBS += -L$$PWD/../../../../../../usr/lib/ -lGLEW

INCLUDEPATH += $$PWD/../../../../../../usr/include
DEPENDPATH += $$PWD/../../../../../../usr/include

RESOURCES += \
    source.qrc

OTHER_FILES += \
    FragmentShaderCode.glsl
