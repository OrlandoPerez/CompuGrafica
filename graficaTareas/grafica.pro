CONFIG +=c++14
TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lGL -lglut -lGLU

SOURCES += main.cpp \
    Polygon.cpp \
    EdgeTable.cpp

HEADERS += \
    Polygon.h \
    EdgeTable.h

