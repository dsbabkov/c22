TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    IAny.cpp \
    Any.cpp \
    WrapAny.cpp

HEADERS += \
    IAny.h \
    Any.h \
    WrapAny.h \
    MyUniquePTR.h

