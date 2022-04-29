linux-g++:CONFIG(release, debug|release) {
  QMAKE_STRIP         =   strip
}

include(../widgets.pri)

TEMPLATE              =   lib

HEADERS               +=  wwglobal.h wwglobal_p.h colormodel.h
SOURCES               +=  wwglobal_p.cpp colormodel.cpp

RESOURCES             +=  ../images/wwwidgets.qrc
INCLUDEPATH           +=  .

CONFIG                +=  warn_on
DSNAME                =   wwwidgets

QT                    +=  widgets

linux-g++ {
  CONFIG              +=  separate_debug_info
}

DEFINES               +=  WW_BUILD_WWWIDGETS

# Extra headers
HDR_INSTALL           +=  $$PWD/wwglobal.h

DOCS_FILES            =   $$PWD/../doc/*
EXAMPLES_FILES        =   $$PWD/../examples/*
PRF_FILE              =   $$PWD/../$${DSNAME}.prf

include($$PWD/../../dscommon/dscfg.pri)

# Destination directory must be one level up
win32:dll:DLLDESTDIR  =   $$OUT_PWD/../../bin
DESTDIR               =   $$OUT_PWD/../../lib
