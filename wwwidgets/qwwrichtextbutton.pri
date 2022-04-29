WD = $$PWD
!headersonly {
  plugin {
    SOURCES += $$WD/plugin/qwwrichtextbuttoniface.cpp
    HEADERS += $$WD/plugin/qwwrichtextbuttoniface.h
  } else {
    SOURCES += $$WD/widgets/qwwrichtextbutton/qwwrichtextbutton.cpp
    HEADERS += $$WD/widgets/qwwrichtextbutton/qwwrichtextbutton.h
  }
}
INCLUDEPATH += $$WD/widgets/qwwrichtextbutton
HDR_INSTALL += $$WD/widgets/qwwrichtextbutton/qwwrichtextbutton.h $$WD/widgets/qwwrichtextbutton/QwwRichTextButton
