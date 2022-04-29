INCLUDEPATH	          +=  $$PWD
DEPENDPATH            +=  $$PWD

HEADERS               +=  $$PWD/qtlockedfile.h
SOURCES               +=  $$PWD/qtlockedfile.cpp
unix:SOURCES          +=  $$PWD/qtlockedfile_unix.cpp
win32:SOURCES         +=  $$PWD/qtlockedfile_win.cpp
HDR_INSTALL           +=  $${HEADERS} QtLockedFile

win32:dll:DEFINES     +=  QT_QTLOCKEDFILE_EXPORT
