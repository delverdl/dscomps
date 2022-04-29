WD = $$PWD
!headersonly {
  plugin {
    SOURCES += $$WD/plugin/qwwlistnavigatoriface.cpp
    HEADERS += $$WD/plugin/qwwlistnavigatoriface.h
  } else {
    SOURCES += $$WD/widgets/qwwlistnavigator/qwwlistnavigator.cpp
    HEADERS += $$WD/widgets/qwwlistnavigator/qwwlistnavigator.h
  }
}
INCLUDEPATH += $$WD/widgets/qwwlistnavigator
HDR_INSTALL += $$WD/widgets/qwwlistnavigator/qwwlistnavigator.h $$WD/widgets/qwwlistnavigator/QwwListNavigator

