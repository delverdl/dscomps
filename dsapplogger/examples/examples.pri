TEMPLATE  =   app

QT        +=  core

CONFIG    +=  dsapplogger

isEmpty(DSSYSTEM) {
  # On local build tree
  include($$PWD/../../dscommon/dscfgbase.pri)

  INCLUDEPATH     +=  $$PWD/.. \
                      $$PWD/../include \
                      $$PWD/../../dscommon

  dsAddLibrary($$OUT_PWD/../../../lib, dsapplogger)

  DESTDIR         =   $$OUT_PWD/../../../bin
  QMAKE_RPATHDIR  *=  $$OUT_PWD/../../../lib
}
