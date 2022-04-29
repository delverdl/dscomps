WD = $$PWD
!headersonly {
  plugin {
    SOURCES += $$WD/plugin/qwwnumpadiface.cpp
    HEADERS += $$WD/plugin/qwwnumpadiface.h
  } else {
    SOURCES += $$WD/widgets/qwwnumpad/qwwnumpad.cpp
    HEADERS += $$WD/widgets/qwwnumpad/qwwnumpad.h
  }
}
INCLUDEPATH += $$WD/widgets/qwwnumpad
HDR_INSTALL += $$WD/widgets/qwwnumpad/qwwnumpad.h $$WD/widgets/qwwnumpad/QwwNumPad
