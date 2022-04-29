TEMPLATE = subdirs

#SUBDIRS = xlsx

DSTMP = $$[QT_SYSROOT]
!android:isEmpty(DSTMP) {
  xinst.files = $$PWD/xlsx
  xinst.path  = $$[QT_INSTALL_EXAMPLES]

  INSTALLS    = xinst
}
DSTMP =
