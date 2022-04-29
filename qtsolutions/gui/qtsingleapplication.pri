INCLUDEPATH           +=  $$PWD $$PWD/../core
DEPENDPATH            +=  $$PWD

SOURCES               +=  $$PWD/qtsingleapplication.cpp
HEADERS               +=  $$PWD/qtsingleapplication.h
HDR_INSTALL           +=  $${HEADERS} QtSingleApplication

win32:dll:DEFINES     +=  QT_QTSINGLEAPPLICATION_EXPORT
