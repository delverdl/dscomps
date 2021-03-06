################################################################
# Qwt Widget Library
# Copyright (C) 1997   Josef Wilgen
# Copyright (C) 2002   Uwe Rathmann
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the Qwt License, Version 1.0
################################################################
include( $$PWD/../qwtconfig.pri )

TEMPLATE        =   subdirs

contains(QWT_CONFIG, QwtExamplesBuild) {
  contains(QWT_CONFIG, QwtPlot) {
    SUBDIRS     +=  plotmatrix timescale scaleengine graphicscale rescaler shapes \
                    curvetracker symbols
    contains(QWT_CONFIG, QwtSvg) {
      SUBDIRS   +=  svgmap
    }
  }
}

iexamples.files =   $$PWD
iexamples.path  =   $${QWT_INSTALL_EXAMPLES}/playground

INSTALLS        +=  iexamples
