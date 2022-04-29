WD = $$PWD
!headersonly {
  plugin {
    SOURCES += $$WD/plugin/qwwrichtexteditiface.cpp
    HEADERS += $$WD/plugin/qwwrichtexteditiface.h
  } else {
    SOURCES += $$WD/widgets/qwwrichtextedit/qwwrichtextedit.cpp
    HEADERS += $$WD/widgets/qwwrichtextedit/qwwrichtextedit.h
  }
}
INCLUDEPATH += $$WD/widgets/qwwrichtextedit
HDR_INSTALL += $$WD/widgets/qwwrichtextedit/qwwrichtextedit.h $$WD/widgets/qwwrichtextedit/QwwRichTextEdit
