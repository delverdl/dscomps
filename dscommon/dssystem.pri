DSSYSTEM          =   NOFRAMEWORK

macx:!static:CONFIG(qt_framework, qt_framework|qt_no_framework)) {
  DSSYSTEM        =   HASFRAMEWORK
  DSSYSTEM        *=  MACOS
}

DSSYSTEM          *=  $$QT_ARCH

unix:DSSYSTEM     *=  UNIX
linux-*:DSSYSTEM  *=  LINUX
win32:DSSYSTEM    *=  WINDOWS

DSTMP = $$[QT_SYSROOT]
android|!isEmpty(DSTMP) {
  DSSYSTEM        *=  TODEVICE
} else {
  DSSYSTEM        *=  TODESKTOP
}
DSTMP =
