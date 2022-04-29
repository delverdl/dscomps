WD = $$PWD
!headersonly {
  plugin {
    SOURCES += $$WD/plugin/qwwclearlineeditiface.cpp
    HEADERS += $$WD/plugin/qwwclearlineeditiface.h
  } else {
    SOURCES += $$WD/widgets/qwwclearlineedit/qwwclearlineedit.cpp
    HEADERS += $$WD/widgets/qwwclearlineedit/qwwclearlineedit.h
  }
}
INCLUDEPATH += $$WD/widgets/qwwclearlineedit
HDR_INSTALL += $$WD/widgets/qwwclearlineedit/qwwclearlineedit.h $$WD/widgets/qwwclearlineedit/QwwClearLineEdit
