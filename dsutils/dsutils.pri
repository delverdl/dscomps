INCLUDEPATH  += $$PWD
DEPENDPATH   += $$PWD

include($$PWD/../dscallback/dscallback.pri)

HDR_INSTALL  =   $$PWD/AppUtils \
                 $$PWD/AppUtils.hpp \
                 $$PWD/CMedia \
                 $$PWD/CMedia.hpp \
                 $$PWD/CoinCodes \
                 $$PWD/CoinCodes.hpp \
                 $$PWD/CPosItem \
                 $$PWD/CPosItem.hpp \
                 $$PWD/interfaces/CAbstractMedia \
                 $$PWD/interfaces/CAbstractMedia.h \
                 $$PWD/interfaces/CAbstractPrinter \
                 $$PWD/interfaces/CAbstractPrinter.h \
                 $$PWD/interfaces/DeviceErrors \
                 $$PWD/interfaces/DeviceErrors.h
HEADERS      +=  $$HDR_INSTALL
