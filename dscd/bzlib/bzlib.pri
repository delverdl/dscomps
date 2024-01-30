INCLUDEPATH += .

# Input

HDR_INSTALL += bzlib.h

HEADERS += bz_version.h bzlib_private.h
SOURCES += blocksort.c \
           bzlib.c \
           compress.c \
           crctable.c \
           decompress.c \
           huffman.c \
           randtable.c

