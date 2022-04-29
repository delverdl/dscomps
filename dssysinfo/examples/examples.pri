TEMPLATE  =   app

QT        *=  core

CONFIG    +=  dssysinfo

isEmpty(DSSYSTEM) {
  # On local build tree
  include($$PWD/../../dscommon/dscfgbase.pri)

  INCLUDEPATH     +=  $$PWD/.. \
                      $$PWD/../../dscommon

  dsAddLibrary($$OUT_PWD/../../../lib, dssysinfo)

  DESTDIR         =   $$OUT_PWD/../../../bin
  QMAKE_RPATHDIR  *=  $$OUT_PWD/../../../lib
}
