HEADERS                     +=  wwwidgets.h wwinterfaces.h colorlisteditor.h
SOURCES                     +=  wwwidgets.cpp wwinterfaces.cpp colorlisteditor.cpp

FORMS                       +=  about.ui colorlisteditor.ui

TEMPLATE                    =   lib
TARGET                      =   wwwidgets_plugin
CONFIG                      +=  plugin warn_on release
CONFIG                      -=  debug

unix:QMAKE_CXXFLAGS_RELEASE -=  -g

# Basic configuration
include($$PWD/../../dscommon/dscfgbase.pri)

dsAddLibrary($$OUT_PWD/../../lib, wwwidgets)

QT                          *=  core gui widgets designer

DESTDIR                     =   $$OUT_PWD/../../plugins

# Installation
target.path                 =   $$DSPLUGINS/designer
INSTALLS                    +=  target

INCLUDEPATH                 +=  $$PWD/../widgets/ .

linux-g++ {
  QMAKE_STRIP               =   strip
}

# Components include paths and interfaces
include($$PWD/../widgets.pri)
