TEMPLATE            =   lib
DSNAME              =   dsarchive

QT                  -=  gui

DEFINES             +=  HAVE_BZIP2_SUPPORT=1 NEED_BZ2_PREFIX=1 HAVE_XZ_SUPPORT=1\

DOCS_FILES          =   $$PWD/doc/*
EXAMPLES_FILES      =   $$PWD/examples/*
PRF_FILE            =   $$PWD/$${DSNAME}.prf

# Sources
include($$PWD/dsarchive.pri)

# Config
include($$PWD/../dscommon/dscfg.pri)

staticlib: DEFINES  +=  KARCHIVE_STATIC_DEFINE

DBG_CHAR            =
win32 {
  CONFIG(debug, release|debug) {
    DBG_CHAR        =   d
  }
  LIBS              +=  -ladvapi32
  DEFINES           +=  _CRT_SECURE_NO_WARNINGS
  msvc: LIBS        +=  -L$$[QT_INSTALL_LIBS]
}
macx:CONFIG(debug, release|debug) {
  DBG_CHAR          =   _debug
}
LIBS                +=  -lz$$DBG_CHAR -lbz2$$DBG_CHAR -llzma$$DBG_CHAR
