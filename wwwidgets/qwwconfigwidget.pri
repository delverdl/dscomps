WD = $$PWD
!headersonly {
  plugin {
    SOURCES += $$WD/plugin/qwwconfigwidgetiface.cpp
    HEADERS += $$WD/plugin/qwwconfigwidgetiface.h
  } else {
    SOURCES += $$WD/widgets/qwwconfigwidget/qwwconfigwidget.cpp
    HEADERS += $$WD/widgets/qwwconfigwidget/qwwconfigwidget.h
    HEADERS += $$WD/widgets/qwwconfigwidget/qwwconfigwidget_p.h
  }
}
INCLUDEPATH += $$WD/widgets/qwwconfigwidget
HDR_INSTALL += $$WD/widgets/qwwconfigwidget/qwwconfigwidget.h $$WD/widgets/qwwconfigwidget/QwwConfigWidget
