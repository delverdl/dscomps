include($$PWD/../dssshexamples.pri)

QT          +=  network

CONFIG      +=  c++11

SOURCES     +=  main.cpp \
                CSshTester.cpp
HEADERS     +=  CSshTester.h

CONFIG      +=  console
