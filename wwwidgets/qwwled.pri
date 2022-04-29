WD = $$PWD
!headersonly {
  plugin {
    SOURCES += $$WD/plugin/qwwlediface.cpp
    HEADERS += $$WD/plugin/qwwlediface.h
  } else {
    SOURCES += $$WD/widgets/qwwled/qwwled.cpp
    HEADERS += $$WD/widgets/qwwled/qwwled.h
  }
}
INCLUDEPATH += $$WD/widgets/qwwled
HDR_INSTALL += $$WD/widgets/qwwled/qwwled.h $$WD/widgets/qwwled/QwwLed
