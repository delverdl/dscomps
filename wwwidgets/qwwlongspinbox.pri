WD = $$PWD
!headersonly {
  plugin {
    SOURCES += $$WD/plugin/qwwlongspinboxiface.cpp
    HEADERS += $$WD/plugin/qwwlongspinboxiface.h
  } else {
    SOURCES += $$WD/widgets/qwwlongspinbox/qwwlongspinbox.cpp
    HEADERS += $$WD/widgets/qwwlongspinbox/qwwlongspinbox.h
  }
}
INCLUDEPATH += $$WD/widgets/qwwlongspinbox
HDR_INSTALL += $$WD/widgets/qwwlongspinbox/qwwlongspinbox.h $$WD/widgets/qwwlongspinbox/QwwLongSpinBox
