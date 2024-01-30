TEMPLATE = lib
CONFIG -= qt
CONFIG += staticlib

include($$PWD/zlib/zlib.pri)
include($$PWD/lzma/lzma.pri)
include($$PWD/bzlib/bzlib.pri)

