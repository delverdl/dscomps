include($$PWD/../dssshexamples.pri)

QT          +=  network

CONFIG      +=  c++11

SOURCES     +=  main.cpp \
                CSftpTester.cpp
HEADERS     +=  CSftpTester.h

CONFIG      +=  console
