#To edit uncomment the following line
#and comment the next assigment
#TEMPLATE        =   lib

#To compile uncomment the following line
#and uncomment the next assignment
TEMPLATE        =   subdirs

include($$PWD/../dscommon/dscfgbase.pri)
include($$PWD/dsutils.pri)

# Header-only callback class factories
iutils.files    =   $$HDR_INSTALL
iutils.path     =   $$DSHEADERS/dsutils

iutlfeats.files =   $$PWD/dsutils.prf
iutlfeats.path  =   $$DSFEATURES

INSTALLS        +=  iutils iutlfeats

