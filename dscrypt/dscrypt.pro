TEMPLATE            =   lib
DSNAME              =   dscrypt

QT                  -=  gui

DEFINES             +=  CRYPT_LIBRARY  _LIB

win32:RC_FILE       =   library.rc

include($$PWD/crypt/crypt.pri)
include($$PWD/math/math.pri)

DOCS_FILES          =   $$PWD/doc/*
EXAMPLES_FILES      =   $$PWD/examples/*
PRF_FILE            =   $$PWD/$${DSNAME}.prf

# Config
include($$PWD/../dscommon/dscfg.pri)

# Encryption/decryption functions are forcedly left inside binary
CONFIG              *=  staticlib
CONFIG              -=  shared dll
