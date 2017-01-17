#-------------------------------------------------
#
# Project created by QtCreator 2017-01-03T07:44:07
#
#-------------------------------------------------


CONFIG +=c++14

QT       += core gui


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Scanner3D
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Capture.cpp

HEADERS  += mainwindow.h \
    Capture.h \
    GLViewer.h

FORMS    += mainwindow.ui


INCLUDEPATH += .
INCLUDEPATH += /usr/local/include
INCLUDEPATH += /usr/local/include/opencv
INCLUDEPATH += /usr/local/include/opencv2
INCLUDEPATH += /usr/local/include/opencv2/core
INCLUDEPATH += /usr/local/include/opencv2/highgui
INCLUDEPATH += /usr/local/include/opencv2/imgproc
INCLUDEPATH += /usr/local/include/opencv2/flann
INCLUDEPATH += /usr/local/include/opencv2/photo
INCLUDEPATH += /usr/local/include/opencv2/video
INCLUDEPATH += /usr/local/include/opencv2/features2d
INCLUDEPATH += /usr/local/include/opencv2/objdetect
INCLUDEPATH += /usr/local/include/opencv2/calib3d
INCLUDEPATH += /usr/local/include/opencv2/ml
INCLUDEPATH += /usr/local/include/opencv2/contrib


LIBS += `pkg-config opencv --cflags --libs`

LIBS += -L"/usr/local/lib" -lCGAL
LIBS +=  -lgmp
LIBS += -lmpfr
#LIBS += -lCGAL -lCGAL_Core
LIBS += -lboost_system
LIBS += -lboost_thread
#DEFINES += CGAL_EIGEN3_ENABLED

QMAKE_CXXFLAGS += -frounding-math


