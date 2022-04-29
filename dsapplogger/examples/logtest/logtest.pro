include($$PWD/../examples.pri)

QT                +=  core
QT                -=  gui

CONFIG            +=  console
CONFIG            -=  app_bundle

SOURCES           +=  main.cpp
