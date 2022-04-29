QT              +=  core gui widgets serialport

TARGET          =   testall
TEMPLATE        =   app

DEFINES         +=  QT_DEPRECATED_WARNINGS
DEFINES         +=  QT_DISABLE_DEPRECATED_BEFORE=0x060000

SOURCES         +=  main.cpp\
                    CTestWindow.cpp \
                    CCryptTest.cpp \
                    CSshTest.cpp \
                    CPropertiesTest.cpp \
                    CWidgetsTest.cpp

HEADERS         +=  CTestWindow.h \
                    CCryptTest.h \
                    CSshTest.h \
                    CPropertiesTest.h \
                    CWidgetsTest.h \
                    TestExceptions.hpp

FORMS           +=  CTestWindow.ui

RESOURCES       +=  testall.qrc

unix: LIBS      +=  -ldl -ludev -lm -lz
win32: LIBS     +=  -lwbemuuid -lnetapi32 -lole32 -loleaut32 -ladvapi32

QT              +=  gui widgets opengl concurrent printsupport svg network

DEFINES         +=  QWT_DLL \
                    LTM_DESC \
                    #LTM_ALL \
                    SC_RSA_1 \
                    DSSYS_INFO_STATIC

CONFIG          +=  silent dsapplogger dscrypt qwt wwwidgets dsssh dssshwidgets qtsgui \
                    dsutils dsarchive dssysinfo
INCLUDEPATH     +=  ./
DEPENDPATH      +=  ./

