include($$PWD/../dscommon/dssystem.pri)

android|contains(DSSYSTEM,TODEVICE) {
  TEMPLATE            =   subdirs
  SUBDIRS             =
} else {
  # SSH library from QtCreator
  TEMPLATE            =   lib
  DSNAME              =   dsssh

  QT                  +=  network
  QT                  -=  gui
  DEFINES             +=  QSSH_LIBRARY

  # Sources
  include(dsssh.pri)
  include($$PWD/botan/dsbotan.pri)

  DOCS_FILES          =   $$PWD/doc/*
  EXAMPLES_FILES      =   $$PWD/examples/*
  PRF_FILE            =   $$PWD/$${DSNAME}.prf

  # Config
  include($$PWD/../dscommon/dscfg.pri)
  include($$PWD/../dscallback/dscallback.pri)

  # Install botan headers in a proper directory apart from QtSsh headers, cuz
  # botan is always included as #include <botan/botan.h>; then its header
  # should be copied into botan directory in DsSsh headers directory
  CONFIG(lib_bundle) {
    FWKBOTAN.version  =   Versions
    FWKBOTAN.files    =   $$BOTANHEADER
    FWKBOTAN.path     =   Headers/botan
    QMAKE_BUNDLE_DATA +=  FWKBOTAN
  } else {
    bothdr.files      =   $$BOTANHEADER
    bothdr.path       =   $$DSHEADERS/$$DSNAME/botan
    INSTALLS          +=  bothdr
  }

  # Install botan docs
  # User must be aware to include "CONFIG += dsssh" in project
  # to use botan crypto funcionality by just including it as:
  # #include <botan/botan.h>
  idocs.files         =   $$PWD/botan/doc/*
  idocs.path          =   $$DSDOCS
}
