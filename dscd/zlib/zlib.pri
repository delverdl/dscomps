INCLUDEPATH += .

HDR_INSTALL += $$PWD/zlib.h

msvc: HDR_INSTALL += $$PWD/msvc/zconf.h
else: HDR_INSTALL += $$PWD/other/zconf.h

# Input
HEADERS += $$PWD/crc32.h \
           $$PWD/deflate.h \
           $$PWD/gzguts.h \
           $$PWD/inffast.h \
           $$PWD/inffixed.h \
           $$PWD/inflate.h \
           $$PWD/inftrees.h \
           $$PWD/trees.h \
           $$PWD/zutil.h \
           $$PWD/inftrees.h \
           $$PWD/inflate.h \
           $$PWD/zutil.h \
           $$PWD/inffast.h
           
SOURCES += $$PWD/adler32.c \
           $$PWD/compress.c \
           $$PWD/crc32.c \
           $$PWD/deflate.c \
           $$PWD/gzclose.c \
           $$PWD/gzlib.c \
           $$PWD/gzread.c \
           $$PWD/gzwrite.c \
           $$PWD/infback.c \
           $$PWD/inffast.c \
           $$PWD/inflate.c \
           $$PWD/inftrees.c \
           $$PWD/trees.c \
           $$PWD/uncompr.c \
           $$PWD/zutil.c
