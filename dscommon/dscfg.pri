include($$PWD/dscfgbase.pri)

win32|osx {
  CONFIG                  *=  debug_and_release
  CONFIG                  *=  build_all
} else {
  CONFIG                  -=  build_all debug debug_and_release
  CONFIG                  *=  release
}

TARGET                    =   $$dsLibraryTarget($$DSNAME)

static {
  CONFIG                  *=  staticlib
  CONFIG                  -=  shared dll
}

!contains(CONFIG, staticlib) {
  CONFIG                  *=  shared dll
  win32 {
    DEFINES               *=  QT_DLL DS_DLL
  }
}

CONFIG                    *=  islib

# Shared object and export library install location
win32:dll {
  dlltarget.path          =   $$DSBINS
  INSTALLS                *=  dlltarget
  DLLDESTDIR              =   $$OUT_PWD/../bin
}
DESTDIR                   =   $$OUT_PWD/../lib

# OSX configuration for libraries
osx {
  CONFIG                  *=  lib_bundle
  dll:QMAKE_LFLAGS_SONAME =   -Wl,-install_name,@rpath/Frameworks/
}

# Installation
idocs.files               =   $$DOCS_FILES
idocs.path                =   $$DSDOCS

iprf.files                =   $$PRF_FILE
iprf.path                 =   $$DSFEATURES

iexamples.files           =   $$EXAMPLES_FILES
iexamples.path            =   $$DSEXAMPLES/$$DSNAME

target.path               =   $$DSLIBS

# Headers install location
CONFIG(lib_bundle) {
  LIBFWK.version          =   Versions
  LIBFWK.files            =   $$HDR_INSTALL
  LIBFWK.path             =   Headers
  QMAKE_BUNDLE_DATA       *=  LIBFWK
} else {
  iheaders.files          =   $$HDR_INSTALL
  iheaders.path           =   $$DSHEADERS/$$DSNAME
  INSTALLS                *=  iheaders
}

!android:!contains(DSSYSTEM,TODEVICE) {
  INSTALLS                *=  idocs iexamples
}

INSTALLS                  *=  iprf target
