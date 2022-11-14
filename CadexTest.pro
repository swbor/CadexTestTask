TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

HEADERS +=

QMAKE_CXXFLAGS += -fopenmp
QMAKE_LFLAGS +=  -fopenmp

LIBS += -lgomp -lpthread
unix:!macx: LIBS += -L$$PWD/Lib/ -lCadexCurvesLibrary

INCLUDEPATH += $$PWD/Lib
DEPENDPATH += $$PWD/Lib


