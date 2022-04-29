TEMPLATE              =   lib
DSNAME                =   qtsgui

QT                    *=  core gui network widgets

DEFINES               +=  QTSGUI_LIBRARY

HEADERS               +=  $$PWD/qtsgui_global.h
HDR_INSTALL           +=  $$HEADERS

# Sources
include($$PWD/qtsingleapplication.pri)
include($$PWD/qtpropertybrowser.pri)

DOCS_FILES            =   $$PWD/doc/*
EXAMPLES_FILES        =   $$PWD/examples/*
PRF_FILE              =   $$PWD/$${DSNAME}.prf

# Config
include($$PWD/../../dscommon/dscfg.pri)

OTHER_FILES           +=  $$PWD/$${DSNAME}.prf

DESTDIR               =   $$OUT_PWD/../../lib
win32:dll:DLLDESTDIR  =   $$OUT_PWD/../../bin

dsAddLibrary($$OUT_PWD/../../lib, qtscore)

DEFINES               +=  QT_QTSERVICE_IMPORT QT_QTLOCKEDFILE_IMPORT \
                          QT_QTSINGLECOREAPPLICATION_IMPORT

