INCLUDEPATH +=  $$PWD

HDR_PUB     +=  \
                $$PWD/CAbstractMedia \
                $$PWD/CAbstractPrinter \
                $$PWD/DeviceErrors

HEADERS     +=  \
                $$PWD/CAbstractMedia.h \
                $$PWD/CAbstractPrinter.h \
                $$PWD/DeviceErrors.h \
                $${HDR_PUB}
