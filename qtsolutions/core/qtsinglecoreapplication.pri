INCLUDEPATH	          +=  $$PWD
DEPENDPATH            +=  $$PWD

SOURCES               +=  $$PWD/qtsinglecoreapplication.cpp $$PWD/qtlocalpeer.cpp
HEADERS               +=  $$PWD/qtsinglecoreapplication.h $$PWD/qtlocalpeer.h
HDR_INSTALL           +=  $${HEADERS} QtLocalPeer QtSingleCoreApplication

win32:dll:DEFINES     +=  QT_QTSINGLECOREAPPLICATION_EXPORT
