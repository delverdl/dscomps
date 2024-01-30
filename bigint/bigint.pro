TEMPLATE            =   lib
DSNAME              =   bigint

HDR_INSTALL         +=  \
                        BigInteger.hh \
                        BigIntegerAlgorithms.hh \
                        BigIntegerLibrary.hh \
                        BigIntegerUtils.hh \
                        BigUnsigned.hh \
                        BigUnsignedInABase.hh \
                        NumberlikeArray.hh

HEADERS             +=  $$HDR_INSTALL     

SOURCES             +=  BigInteger.cc \
                        BigIntegerAlgorithms.cc \
                        BigIntegerUtils.cc \
                        BigUnsigned.cc \
                        BigUnsignedInABase.cc

INCLUDEPATH         =   .

PRF_FILE            =   $$PWD/$${DSNAME}.prf

# Config
include($$PWD/../dscommon/dscfg.pri)

# No documentation or examples
INSTALLS            -=  idocs iexamples

# This is not a Qt library/binary
CONFIG              -=  qt
