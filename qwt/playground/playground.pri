################################################################
# Qwt Widget Library
# Copyright (C) 1997   Josef Wilgen
# Copyright (C) 2002   Uwe Rathmann
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the Qwt License, Version 1.0
###################################################################
CONFIG          +=  qwt

QWT_ROOT        =   $$PWD/..
isEmpty(DSSYSTEM) {
  include( $${QWT_ROOT}/qwtconfig.pri )
  include( $${QWT_ROOT}/qwtbuild.pri )
}

QWT_OUT_ROOT    =   $${OUT_PWD}/../../..

TEMPLATE        =   app

INCLUDEPATH     +=  $${QWT_ROOT}/src
DEPENDPATH      +=  $${QWT_ROOT}/src

!debug_and_release {
  DESTDIR       =   $${QWT_OUT_ROOT}/playground/bin
}
else {
  CONFIG(debug, debug|release) {
    DESTDIR     =   $${QWT_OUT_ROOT}/playground/bin_debug
  }
  else {
    DESTDIR     =   $${QWT_OUT_ROOT}/playground/bin
  }
}

QMAKE_RPATHDIR  *=  $${QWT_OUT_ROOT}/lib
dsAddLibrary($${QWT_OUT_ROOT}/lib, qwt)
