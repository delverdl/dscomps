TEMPLATE        =   subdirs

CONFIG          +=  ordered

include($$PWD/dscommon/dscfgbase.pri)

!wasm {
  SUBDIRS       +=  dsposprn \
                    dsssh \
                    dssshwidgets \
                    dssysinfo \
                    qwt
}

SUBDIRS         +=  \
                    bigint \
                    dsarchive \
                    dscallback \
                    dsutils \
                    qxlsx \
                    dscrypt \
                    dsapplogger \
                    qtsolutions \
                    qzxing \
                    wwwidgets
                    
icommons.files  =   $$PWD/dscommon/dsfuncs.pri \
                    $$PWD/dscommon/dssystem.pri \
                    $$PWD/dscommon/dscfgbase.pri 
icommons.path   =   $$DSFEATURES

INSTALLS        +=   icommons
