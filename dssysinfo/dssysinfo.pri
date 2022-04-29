SOURCES             +=  $$PWD/CCommonConnector.cpp \
                        $$PWD/CCommonInfo.cpp \
                        $$PWD/CSysInfo.cpp

HDR_PRIVATE         +=  $$PWD/CCommonConnector.h \
                        $$PWD/CCommonInfo.h \
                        $$PWD/CSysInfo_p.h

HDR_INSTALL         +=  $$PWD/dstypes.h \
                        $$PWD/CInformer.h \
                        $$PWD/CConnector.h \
                        $$PWD/CSysInfo.h \
                        $$PWD/CDisk.h

HEADERS             +=  $$HDR_PRIVATE $$HDR_INSTALL

win32 {
  SOURCES           +=  $$PWD/windows/CWin32Info.cpp \
                        $$PWD/windows/CClassObject.cpp \
                        $$PWD/windows/CWmiConnector.cpp
  HEADERS           +=  $$PWD/windows/CWin32Info.h \
                        $$PWD/windows/CClassObject.h \
                        $$PWD/windows/CWmiConnector.h
  INCLUDEPATH       +=  $$PWD/windows
  LIBS              +=  -lwbemuuid -lnetapi32 -lole32 -loleaut32 -ladvapi32
  DEFINES           +=  _WIN32_DCOM _CRT_SECURE_NO_WARNINGS
} else {
  SOURCES           +=  $$PWD/unix/CUnix32Info.cpp \
                        $$PWD/unix/CUdevConnector.cpp
  HEADERS           +=  $$PWD/unix/CUnix32Info.h \
                        $$PWD/unix/CUdevConnector.h
  INCLUDEPATH       +=  $$PWD/unix
  LIBS              +=  -ludev -lm -lz
}
