# dscomps
Qt set of components

This is a small set of Qt components which will help you create C/C++ applications with this amazing framework.

* dsapplogger: It's a simple library for adding logs funtionality to your applications
* dsarchive: It's KDE's karchive library
* dscallback: It a pure C++ implementation of callbacks but faster than std::bind
* dscrypt: It's Tomcrypt and Tommath libraries (https://github.com/libtom/libtomcrypt), but they can be build using qmake and a decent compiler.
* dsposprn: It's a plugin for using in ESC/POS printers protocol.
* dsssh: It's old Qt creator's SSH client.
* dssshwidget: GUI libraries supporting dsssh.
* dssysinfo: System information library using Windows WMI and UDEV in Linux.
* dsutils: Some utilities classes.
* qtsolutions: Set of Qt Solution classes.
* qtxlsx: Qt library for reading and writing XLSX files.
* qwt: QWT libraries.
* wwwidgets: Some GUI components.

I implemented dsapplogger, dsposprn, dssysinfo and dsutils. I've tested compiling the whole package with Qt for Windows, Linux, MacOS and Android.

Any suggestions on improving this are very welcome.
