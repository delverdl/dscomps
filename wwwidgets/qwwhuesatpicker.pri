WD = $$PWD
!headersonly {
  plugin {
    SOURCES += $$WD/plugin/qwwhuesatpickeriface.cpp
    HEADERS += $$WD/plugin/qwwhuesatpickeriface.h
  } else {
    SOURCES += $$WD/widgets/qwwhuesatpicker/qwwhuesatpicker.cpp
    HEADERS += $$WD/widgets/qwwhuesatpicker/qwwhuesatpicker.h
  }
}
INCLUDEPATH += $$WD/widgets/qwwhuesatpicker
HDR_INSTALL += $$WD/widgets/qwwhuesatpicker/qwwhuesatpicker.h $$WD/widgets/qwwhuesatpicker/QwwHueSatPicker
