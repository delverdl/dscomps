TEMPLATE              =   lib
DSNAME                =   qtscore

QT                    +=  core network
QT                    -=  gui

DEFINES               +=  QTSCORE_LIBRARY
HEADERS               +=  $$PWD/qtscore_global.h
HDR_INSTALL           +=  $$HEADERS

# Sources
include($$PWD/qtlockedfile.pri)
!wasm:include($$PWD/qtservice.pri)
include($$PWD/qtsinglecoreapplication.pri)

DOCS_FILES            =   $$PWD/doc/*
EXAMPLES_FILES        =   $$PWD/examples/*
PRF_FILE              =   $$PWD/$${DSNAME}.prf

# Config
include($$PWD/../../dscommon/dscfg.pri)

DESTDIR               =   $$OUT_PWD/../../lib
win32:dll:DLLDESTDIR  =   $$OUT_PWD/../../bin
