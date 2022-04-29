TEMPLATE        =   subdirs

CONFIG          +=  ordered

include($$PWD/dscommon/dscfgbase.pri)

SUBDIRS         +=  \
                    dsarchive \
                    dscallback \
                    dsutils \
                    dsposprn \
                    qtxlsx \
                    dscrypt \
                    dsapplogger \
                    dssysinfo \
                    dsssh \
                    dssshwidgets \
                    qtsolutions \
                    qwt \
                    wwwidgets

icommons.files  =   $$PWD/dscommon/dsfuncs.pri \
                    $$PWD/dscommon/dssystem.pri \
                    $$PWD/dscommon/dscfgbase.pri 
icommons.path   =   $$DSFEATURES

INSTALLS        +=   icommons
