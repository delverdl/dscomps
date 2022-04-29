INCLUDEPATH         +=  $$PWD/src

HDR_INSTALL         =   $$PWD/src/k7zip.h                 $$PWD/src/kar.h                   $$PWD/src/karchive.h \
                        $$PWD/src/karchive_export.h       $$PWD/src/karchivedirectory.h     $$PWD/src/karchiveentry.h \
                        $$PWD/src/karchivefile.h          $$PWD/src/kcompressiondevice.h    $$PWD/src/kfilterbase.h \
                        $$PWD/src/kfilterdev.h            $$PWD/src/krcc.h                  $$PWD/src/ktar.h  \
                        $$PWD/src/kzip.h                  $$PWD/src/kzipfileentry.h
           
HDR_PRIVATE         =   $$PWD/src/karchive_p.h            $$PWD/src/klimitediodevice_p.h    $$PWD/src/loggingcategory.h \
                        $$PWD/src/kbzip2filter.h          $$PWD/src/kgzipfilter.h           $$PWD/src/knonefilter.h \
                        $$PWD/src/kxzfilter.h

# Input
SOURCES             +=  $$PWD/src/k7zip.cpp               $$PWD/src/kar.cpp                 $$PWD/src/karchive.cpp \
                        $$PWD/src/kbzip2filter.cpp        $$PWD/src/kcompressiondevice.cpp  $$PWD/src/kfilterbase.cpp \
                        $$PWD/src/kfilterdev.cpp          $$PWD/src/kgzipfilter.cpp         $$PWD/src/klimitediodevice.cpp \
                        $$PWD/src/knonefilter.cpp         $$PWD/src/krcc.cpp                $$PWD/src/ktar.cpp \
                        $$PWD/src/kxzfilter.cpp           $$PWD/src/kzip.cpp                $$PWD/src/loggingcategory.cpp

HEADERS             +=  $$HDR_INSTALL $$HDR_PRIVATE

HDR_INSTALL         +=  $$PWD/src/inc/K7Zip               $$PWD/src/inc/KAr               $$PWD/src/inc/KArchive \
                        $$PWD/src/inc/KArchiveDirectory   $$PWD/src/inc/KArchiveEntry     $$PWD/src/inc/KArchiveFile \
                        $$PWD/src/inc/KCompressionDevice  $$PWD/src/inc/KFilterBase       $$PWD/src/inc/KFilterDev \
                        $$PWD/src/inc/KTar                $$PWD/src/inc/KZip              $$PWD/src/inc/KZipFileEntry
