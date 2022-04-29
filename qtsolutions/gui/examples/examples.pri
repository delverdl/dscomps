TEMPLATE  =   app

QT        +=  core gui network widgets

CONFIG    +=  qtsgui

isEmpty(DSSYSTEM) {
  # On local build tree
  include($$PWD/../../../dscommon/dscfgbase.pri)

  INCLUDEPATH     +=  $$PWD/.. \
                      $$PWD/../../../dscommon

  dsAddLibrary($$OUT_PWD/../../../../../lib, qtscore)
  dsAddLibrary($$OUT_PWD/../../../../../lib, qtsgui)

  DESTDIR         =   $$OUT_PWD/../../../../../bin
  QMAKE_RPATHDIR  *=  $$OUT_PWD/../../../../../lib

  DEFINES         +=  QT_QTSERVICE_IMPORT \
                      QT_QTLOCKEDFILE_IMPORT \
                      QT_QTSINGLECOREAPPLICATION_IMPORT \
                      QT_QTPROPERTYBROWSER_IMPORT \
                      QT_QTSINGLEAPPLICATION_IMPORT

}
