#-------------------------------------------------
#
# Project created by QtCreator 2014-06-16T10:51:07
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtOpencv
TEMPLATE = app
QMAKE_CXXFLAGS = -std=c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    meglwidget.cpp \
    Primitives/shapegenerator.cpp

HEADERS  += mainwindow.h \
    meglwidget.h \
    ui_mainwindow.h \
    Primitives/Vertex.h \
    Primitives/shapedata.h \
    Primitives/shapegenerator.h

FORMS    += mainwindow.ui

unix:!macx: LIBS += -L$$PWD/../../../../../../usr/lib/ -lGLEW

INCLUDEPATH += $$PWD/../../../../../../usr/include
DEPENDPATH += $$PWD/../../../../../../usr/include

RESOURCES += \
    source.qrc

OTHER_FILES += \
    FragmentShaderCode.glsl
