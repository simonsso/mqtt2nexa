CONFIG += qt debug
TEMPLATE = app
TARGET =

DEPENDPATH  += . src
INCLUDEPATH += . src
LIBS += -lmosquittopp -lmosquitto

target.path = /usr/local/bin/
INSTALLS += target

# Input
SOURCES += main.cpp

SOURCES += MosqConnect.cpp
HEADERS += MosqConnect.h

SOURCES += tellstick.cpp
HEADERS += tellstick.h

SOURCES += targetvalues.cpp
HEADERS += targetvalues.h
