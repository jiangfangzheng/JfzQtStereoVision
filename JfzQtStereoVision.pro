#-------------------------------------------------
#
# Project created by QtCreator 2017-09-09T14:05:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = JfzQtStereoVision
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH+= D:/Library/OpenCV3.3/build/include\
              D:/Library/OpenCV3.3/build/include/opencv\
              D:/Library/OpenCV3.3/build/include/opencv2

LIBS += D:\Library\OpenCV3.3\build\x64\vc14\lib\opencv_world330.lib    \
        D:\Library\OpenCV3.3\build\x64\vc14\lib\opencv_world330d.lib

SOURCES += \
        main.cpp \
        MainWindow.cpp \
    QtOpenCVTools.cpp

HEADERS += \
        MainWindow.h \
    QtOpenCVTools.h

FORMS += \
        MainWindow.ui


