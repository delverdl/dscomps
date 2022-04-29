################################################################
# Qwt Widget Library
# Copyright (C) 1997   Josef Wilgen
# Copyright (C) 2002   Uwe Rathmann
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the Qwt License, Version 1.0
###################################################################
CONFIG          +=  qwt

isEmpty(DSSYSTEM) {
  QWT_ROOT        =   $$PWD/..

  include( $${QWT_ROOT}/qwtconfig.pri )
  include( $${QWT_ROOT}/qwtbuild.pri )

  QWT_OUT_ROOT    =   $${OUT_PWD}/../../..

  TEMPLATE        =   app

  INCLUDEPATH     +=  $${QWT_ROOT}/src
  DEPENDPATH      +=  $${QWT_ROOT}/src

  QMAKE_RPATHDIR  *=  $${QWT_OUT_ROOT}/lib
  dsAddLibrary($${QWT_OUT_ROOT}/lib, qwt)
} else {
  # For building within installation directory
  QWT_OUT_ROOT    *=  $${OUT_PWD}
}

!debug_and_release {
  DESTDIR       =   $${QWT_OUT_ROOT}/examples/bin
}
else {
  CONFIG(debug, debug|release) {
    DESTDIR     =   $${QWT_OUT_ROOT}/examples/bin_debug
  }
  else {
    DESTDIR     =   $${QWT_OUT_ROOT}/examples/bin
  }
}
