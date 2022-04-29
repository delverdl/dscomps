WD = $$PWD
!headersonly {
  plugin {
    SOURCES += $$WD/plugin/qwwloginboxiface.cpp
    HEADERS += $$WD/plugin/qwwloginboxiface.h
  } else {
    SOURCES += $$WD/widgets/qwwloginbox/qwwloginbox.cpp
    HEADERS += $$WD/widgets/qwwloginbox/qwwloginbox.h
    FORMS   += $$WD/widgets/qwwloginbox/loginbox.ui
  }
}
INCLUDEPATH += $$WD/widgets/qwwloginbox
HDR_INSTALL += $$WD/widgets/qwwloginbox/qwwloginbox.h $$WD/widgets/qwwloginbox/QwwLoginBox
