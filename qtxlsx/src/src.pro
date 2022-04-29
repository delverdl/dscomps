TEMPLATE = subdirs

SUBDIRS = xlsx

DSTMP = $$[QT_SYSROOT]
!android:isEmpty(DSTMP) {
  idocs.files = $$PWD/doc/*
  idocs.path = $$[QT_INSTALL_DOCS]
}
DSTMP =
