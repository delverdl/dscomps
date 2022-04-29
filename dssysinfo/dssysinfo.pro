android {
  TEMPLATE            =   subdirs
  SUBDIRS             =
} else {
  # System information library
  TEMPLATE            =   lib
  DSNAME              =   dssysinfo

  QT                  +=  network
  QT                  -=  gui

  DEFINES             +=  DSSYS_INFO_LIBRARY

  # Sources
  include($$PWD/dssysinfo.pri)

  !msvc:QMAKE_CXXFLAGS+=  -Wno-write-strings

  DOCS_FILES          =   $$PWD/doc/*
  EXAMPLES_FILES      =   $$PWD/examples/*
  PRF_FILE            =   $$PWD/$${DSNAME}.prf

  # Config
  include($$PWD/../dscommon/dscfg.pri)

}
