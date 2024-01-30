#  Projects common configuration
include(./dsfuncs.pri)

OBJECTS_DIR               =   $$OUT_PWD/obj
MOC_DIR                   =   $$OUT_PWD/moc
UI_DIR                    =   $$OUT_PWD/ui
RCC_DIR                   =   $$OUT_PWD/resources

DEFINES                   +=  QT_DISABLE_DEPRECATED_BEFORE=0x060000 QT_DEPRECATED_WARNINGS

DSDOCS                    =   $$[QT_INSTALL_DOCS]
DSEXAMPLES                =   $$[QT_INSTALL_EXAMPLES]
DSFEATURES                =   $$[QT_HOST_DATA]/mkspecs/features
DSLIBS                    =   $$[QT_INSTALL_LIBS]
DSHEADERS                 =   $$[QT_INSTALL_HEADERS]
DSBINS                    =   $$[QT_INSTALL_BINS]
DSPLUGINS                 =   $$[QT_INSTALL_PLUGINS]

