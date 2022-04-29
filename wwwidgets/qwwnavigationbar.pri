WD = $$PWD
!headersonly {
  plugin {
    SOURCES += $$WD/plugin/qwwnavigationbariface.cpp
    HEADERS += $$WD/plugin/qwwnavigationbariface.h
  } else {
    SOURCES += $$WD/widgets/qwwnavigationbar/qwwnavigationbar.cpp
    HEADERS += $$WD/widgets/qwwnavigationbar/qwwnavigationbar.h
  }
}
INCLUDEPATH += $$WD/widgets/qwwnavigationbar
HDR_INSTALL += $$WD/widgets/qwwnavigationbar/qwwnavigationbar.h $$WD/widgets/qwwnavigationbar/QwwNavigationBar
