TEMPLATE  =   app

CONFIG    +=  dsssh

isEmpty(DSSYSTEM) {
  # On local build tree
  include($$PWD/../../dscommon/dscfgbase.pri)

  CONFIG          +=  c++11

  INCLUDEPATH     +=  $$PWD/.. \
                      $$PWD/../inc \
                      $$PWD/../../dscommon

  dsAddLibrary($$OUT_PWD/../../../lib, dsssh)

  unix: LIBS      +=  -ldl

  DESTDIR         =   $$OUT_PWD/../../../examples/bin

  QMAKE_RPATHDIR  *=  $$OUT_PWD/../../../lib
}
