WD = $$PWD
!headersonly {
  plugin {
    SOURCES += $$WD/plugin/qwwfilechooseriface.cpp
    HEADERS += $$WD/plugin/qwwfilechooseriface.h
  } else {
    SOURCES += $$WD/widgets/qwwfilechooser/qwwfilechooser.cpp
    HEADERS += $$WD/widgets/qwwfilechooser/qwwfilechooser.h
  }
}
INCLUDEPATH += $$WD/widgets/qwwfilechooser
HDR_INSTALL += $$WD/widgets/qwwfilechooser/qwwfilechooser.h $$WD/widgets/qwwfilechooser/QwwFileChooser
