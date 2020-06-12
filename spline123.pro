TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += src
INCLUDEPATH += lib
INCLUDEPATH += /usr/include/eigen3
INCLUDEPATH += $$system(root-config --incdir)

LIBS += $$system(root-config --libs)

SOURCES += \
    examples/example1d.cpp \
    src/profileHist.cpp \
    src/bspline123d.cpp \
    src/bsfit123.cpp \
    lib/json11.cpp

HEADERS += \
    src/profileHist.h \
    src/bsfit123.h \
    src/bspline123d.h \
    lib/eiquadprog.hpp \
    lib/json11.hpp

