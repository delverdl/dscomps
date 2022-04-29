include($$PWD/../dscommon/dssystem.pri)

android|contains(DSSYSTEM,TODEVICE) {
  TEMPLATE            =   subdirs
  SUBDIRS             =
} else {
  # System information library
  TEMPLATE            =   lib
  DSNAME              =   dssshwidgets

  QT                  *=  network
  DEFINES             +=  QSSHWIDGETS_LIBRARY

  INCLUDEPATH         +=  $$PWD/../dsssh \
                          $$PWD/../dscommon

  # Sources
  include(dssshwidgets.pri)

  DOCS_FILES          =   $$PWD/doc/*
  EXAMPLES_FILES      =   $$PWD/examples/*
  PRF_FILE            =   $$PWD/$${DSNAME}.prf

  # Config
  include($$PWD/../dscommon/dscfg.pri)
  include($$PWD/../dscallback/dscallback.pri)

  RESOURCES           +=  $$PWD/dssshwidgets.qrc
}
