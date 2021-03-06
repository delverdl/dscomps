################################################################
# Sumplementary functions
# Copyright (C) 2017   Delver Domingo
#
# This library is free software; you can redistribute it and/or
# modify it.
################################################################
# Copied from old qt_functions.prf. This is a Qwt bright idea.

include(./dssystem.pri)

defineReplace(dsLibraryTarget) {
  unset(LIBRARY_NAME)
  LIBRARY_NAME = $$1
  contains(DSSYSTEM, HASFRAMEWORK) {
    QMAKE_FRAMEWORK_BUNDLE_NAME = $$LIBRARY_NAME
    export(QMAKE_FRAMEWORK_BUNDLE_NAME)
  }
  contains(TEMPLATE, .*lib):CONFIG(debug, debug|release) {
    !debug_and_release|build_pass {
      mac:RET = $$member(LIBRARY_NAME, 0)_debug
      win32:RET = $$member(LIBRARY_NAME, 0)d
    }
  }
  isEmpty(RET):RET = $$LIBRARY_NAME
  return($$RET)
}

defineTest(dsAddLibrary) {
  LIB_PATH = $$1
  LIB_NAME = $$2
  contains(DSSYSTEM, HASFRAMEWORK) {
    LIBS *= -F$${LIB_PATH}
  }
  else {
    unix:lessThan(QT_MAJOR_VERSION, 5) {
      QMAKE_LIBDIR_FLAGS *= -L$${LIB_PATH}
    }
    else {
      LIBS *= -L$${LIB_PATH}
    }
  }
  unset(LINKAGE)
  contains(DSSYSTEM, HASFRAMEWORK) {
    LINKAGE = -framework $${LIB_NAME}
  }
  isEmpty(LINKAGE) {
    if(!debug_and_release|build_pass):CONFIG(debug, debug|release) {
      mac:LINKAGE = -l$${LIB_NAME}_debug
      win32:LINKAGE = -l$${LIB_NAME}d
    }
  }
  isEmpty(LINKAGE):LINKAGE = -l$${LIB_NAME}
  !isEmpty(QMAKE_LSB):QMAKE_LFLAGS *= --lsb-shared-libs=$${LIB_NAME}
  LIBS += $$LINKAGE
  export(LIBS)
  export(QMAKE_LFLAGS)
  export(QMAKE_LIBDIR_FLAGS)
  return(true)
}
