#To edit uncomment the following line
#and comment the next assigment
#TEMPLATE        =   lib

#To compile uncomment the following line
#and uncomment the next assignment
TEMPLATE        =   subdirs

include($$PWD/../dscommon/dscfgbase.pri)
include($$PWD/dscallback.pri)

# Header-only callback class factories
icallback.files =   $$HEADERS
icallback.path  =   $$DSHEADERS/dscallback

icbfeats.files  =   $$PWD/dscallback.prf
icbfeats.path   =   $$DSFEATURES

INSTALLS        +=  icallback icbfeats
