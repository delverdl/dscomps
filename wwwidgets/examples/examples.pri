TEMPLATE          =   app

QT                +=  widgets

CONFIG            +=  wwwidgets

isEmpty(DSSYSTEM) {
  # On local build tree
  include($$PWD/../../dscommon/dscfgbase.pri)

  INCLUDEPATH     +=  $$PWD/../widgets \
                      $$PWD/../../dscommon

  dsAddLibrary($$OUT_PWD/../../../lib, wwwidgets)

  DESTDIR         =   $$OUT_PWD/../../../examples/bin

  QMAKE_RPATHDIR  *=  $$OUT_PWD/../../../lib

  # Include widgets headers paths
  CONFIG          +=  headersonly
  include($$PWD/../widgets.pri)
}
