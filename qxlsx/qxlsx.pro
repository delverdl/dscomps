# QXlsx.pro

DSNAME = qxlsx
TEMPLATE = lib

QXLSX_PARENTPATH=$$PWD/
QXLSX_HEADERPATH=$$PWD/header/
QXLSX_SOURCEPATH=$$PWD/source/
include($$PWD/QXlsx.pri)

DOCS_FILES          =   $$PWD/doc/*
EXAMPLES_FILES      =   $$PWD/examples/*
PRF_FILE            =   $$PWD/$${DSNAME}.prf

# Config
include($$PWD/../dscommon/dscfg.pri)
