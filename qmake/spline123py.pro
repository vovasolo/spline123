TEMPLATE = lib
CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt

TARGET = spline

QMAKE_CXXFLAGS += -O2
QMAKE_CXXFLAGS += -fPIC

INCLUDEPATH += src
INCLUDEPATH += lib
INCLUDEPATH += /usr/include/eigen3
QMAKE_CXXFLAGS += $$system(python3 -m pybind11 --includes)

SOURCES += \
    src/profileHist.cpp \
    src/bspline123d.cpp \
    src/bsfit123.cpp \
    lib/json11.cpp \
    python/wrap.cpp

HEADERS += \
    src/profileHist.h \
    src/bsfit123.h \
    src/bspline123d.h \
    lib/eiquadprog.hpp \
    lib/json11.hpp

