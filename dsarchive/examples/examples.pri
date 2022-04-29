CONFIG  +=  dsarchive

DEFINES +=  QT_DEPRECATED_WARNINGS QT_DISABLE_DEPRECATED_BEFORE=0x060000

LIBS += -L$$OUT_PWD/../../../lib -ldsarchive -llzma -lbz2
INCLUDEPATH += $$PWD/../../src $$PWD/../../src/inc
