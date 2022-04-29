QT          *=  gui widgets

INCLUDEPATH +=  $$PWD
DEPENDPATH  +=  $$PWD

SOURCES     =   $$PWD/sshkeycreationdialog.cpp \
                $$PWD/sftpfilesystemmodel.cpp

HDR_INSTALL =   $$PWD/sshkeycreationdialog.h \
                $$PWD/sftpfilesystemmodel.h \
                $$PWD/sshwidgets_global.h \
                $$PWD/inc/SftpFileSystemModel \
                $$PWD/inc/SshKeyCreationDialog

HEADERS     =   $$HDR_INSTALL

FORMS       =   $$PWD/sshkeycreationdialog.ui

LIBS        +=  -L$$OUT_PWD/../lib -ldsssh
