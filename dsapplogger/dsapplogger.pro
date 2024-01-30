TEMPLATE            =   lib
DSNAME              =   dsapplogger

QT                  -=  gui

DEFINES             +=  APPLOGGER_LIBRARY

SOURCES             +=  CAppLogger.cpp

HDR_INSTALL         +=  $$PWD/include/CAppLogger.h \
                        $$PWD/include/CAppLogger

HEADERS             +=  $$HDR_INSTALL

INCLUDEPATH         =   $$PWD/include

win32 {
  RC_FILE           =   library.rc
  #CONFIG            *=  staticlib
}

DOCS_FILES          =   $$PWD/doc/*
EXAMPLES_FILES      =   $$PWD/examples/*
PRF_FILE            =   $$PWD/$${DSNAME}.prf

# Config
include($$PWD/../dscommon/dscfg.pri)
