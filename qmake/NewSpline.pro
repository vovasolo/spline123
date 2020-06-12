TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += /usr/include/eigen3
INCLUDEPATH += $$system(root-config --incdir)
LIBS += $$system(root-config --libs)

SOURCES += \
    test1D.C \
    profileHist.cpp \
    bsfit123.cpp \
    json11.cpp \
    bspline123d.cpp

HEADERS += \
    profileHist.h \
    bsfit123.h \
    eiquadprog.hpp \
    json11.hpp \
    bspline123d.h
