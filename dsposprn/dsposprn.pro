android {
  TEMPLATE        =   subdirs
  SUBDIRS         =
} else {
  QT              +=  core gui serialport network

  DSNAME          =   dsposprn
  TEMPLATE        =   lib
  CONFIG          +=  plugin static
  CONFIG          -=  shared dll

  include($$PWD/../dscommon/dscfgbase.pri)
  include($$PWD/../dsutils/dsutils.pri)

  SOURCES         +=  CPosPrinter.cpp
  HEADERS         +=  CPosPrinter.h
  DISTFILES       +=  dsposprn.json

  DESTDIR         =   $$OUT_PWD/../plugins

  ippfeats.files  =   $$PWD/$${DSNAME}.prf
  ippfeats.path   =   $$DSFEATURES

  idocs.files     =   $$PWD/doc/*
  idocs.path      =   $$DSDOCS

  target.path     =   $$DSPLUGINS

  INSTALLS        +=  ippfeats target

  !android:!contains(DSSYSTEM,TODEVICE) {
    INSTALLS      *=  idocs
  }

  win32|osx {
    CONFIG        *=  debug_and_release
    CONFIG        *=  build_all
  } else {
    CONFIG        -=  build_all debug debug_and_release
    CONFIG        *=  release
  }

  TARGET          =   $$dsLibraryTarget($$DSNAME)
}
