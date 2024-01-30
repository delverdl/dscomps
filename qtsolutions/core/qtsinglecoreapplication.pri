INCLUDEPATH	          +=  $$PWD
DEPENDPATH            +=  $$PWD

SOURCES               +=  $$PWD/qtsinglecoreapplication.cpp
HEADERS               +=  $$PWD/qtlocalpeer.h $$PWD/qtsinglecoreapplication.h
HDR_INSTALL           +=  $${HEADERS} QtLocalPeer QtSingleCoreApplication

win32:dll:DEFINES     +=  QT_QTSINGLECOREAPPLICATION_EXPORT
