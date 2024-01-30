include($$PWD/../examples.pri)

QT          *=  core network
QT          -=  gui

TARGET      =   ksystest
CONFIG      *=  console dssysinfo
CONFIG      -=  app_bundle

SOURCES     =   main.cpp

INCLUDEPATH +=  .
