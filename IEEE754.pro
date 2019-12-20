TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

#QMAKE_CXXFLAGS -= O2

SOURCES += \
        main.cpp \
    tsdev/test/reporter.cpp \
    tsdev/test/scenario.cpp \
    tsdev/test/test.cpp \
    tests/fixedpoint.cpp

HEADERS += \
    adder.h \
    binary.h \
    bitvector.h \
    fixedpoint.h \
    position.h \
    report.h \
    direction.h \
    range.h \
    tsdev/test/reporter.h \
    tsdev/test/function.h \
    tsdev/test/scenario.h \
    tsdev/test/exception.h \
    tsdev/test/test.h \
    tests/fixedpoint.h
