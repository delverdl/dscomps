INCLUDEPATH	          +=  $$PWD
DEPENDPATH            +=  $$PWD

win32 {
  SOURCES             +=  $$PWD/qtservice_win.cpp
  LIBS                +=  -luser32
  dll:DEFINES         +=  QT_QTSERVICE_EXPORT
} else {
  HEADERS             +=  $$PWD/qtunixsocket.h $$PWD/qtunixserversocket.h
  SOURCES             +=  $$PWD/qtservice_unix.cpp $$PWD/qtunixsocket.cpp $$PWD/qtunixserversocket.cpp
}

HDR_PUBLIC            =   $$PWD/qtservice.h

HEADERS               +=  $${HDR_PUBLIC} $$PWD/qtservice_p.h
SOURCES               +=  $$PWD/qtservice.cpp

HDR_INSTALL           +=  $${HDR_PUBLIC} QtService QtServiceBase QtServiceController
