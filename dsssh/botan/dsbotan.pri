INCLUDEPATH       +=  $$PWD
DEPENDPATH        +=  $$PWD

CONFIG            +=  exceptions

HEADERS           +=  $$PWD/botan.h
SOURCES           +=  $$PWD/botan.cpp

BOTANHEADERS      =   $$HEADERS

# Definitions and compiler options
DEFINES           +=  BOTAN_DLL=Q_DECL_EXPORT
unix:DEFINES      +=  BOTAN_TARGET_OS_HAS_GETTIMEOFDAY BOTAN_HAS_ALLOC_MMAP \
                      BOTAN_HAS_ENTROPY_SRC_DEV_RANDOM BOTAN_HAS_ENTROPY_SRC_EGD \
                      BOTAN_HAS_ENTROPY_SRC_FTW BOTAN_HAS_ENTROPY_SRC_UNIX \
                      BOTAN_HAS_MUTEX_PTHREAD BOTAN_HAS_PIPE_UNIXFD_IO
*linux*:DEFINES   +=  BOTAN_TARGET_OS_IS_LINUX BOTAN_TARGET_OS_HAS_CLOCK_GETTIME \
                      BOTAN_TARGET_OS_HAS_DLOPEN BOTAN_TARGET_OS_HAS_GMTIME_R \
                      BOTAN_TARGET_OS_HAS_POSIX_MLOCK \
                      BOTAN_HAS_DYNAMICALLY_LOADED_ENGINE BOTAN_HAS_DYNAMIC_LOADER
macx:DEFINES      +=  BOTAN_TARGET_OS_IS_DARWIN
*g++*:DEFINES     +=  BOTAN_BUILD_COMPILER_IS_GCC
*clang*:DEFINES   +=  BOTAN_BUILD_COMPILER_IS_CLANG
*icc*:DEFINES     +=  BOTAN_BUILD_COMPILER_IS_INTEL

CONFIG(x86_64) {
  DEFINES         +=  BOTAN_TARGET_ARCH_IS_X86_64
}

win32 {
  DEFINES         +=  BOTAN_TARGET_OS_IS_WINDOWS \
                      BOTAN_TARGET_OS_HAS_LOADLIBRARY \
                      BOTAN_TARGET_OS_HAS_WIN32_GET_SYSTEMTIME \
                      BOTAN_TARGET_OS_HAS_WIN32_VIRTUAL_LOCK \
                      BOTAN_HAS_DYNAMICALLY_LOADED_ENGINE \
                      BOTAN_HAS_DYNAMIC_LOADER BOTAN_HAS_ENTROPY_SRC_CAPI \
                      BOTAN_HAS_ENTROPY_SRC_WIN32 BOTAN_HAS_MUTEX_WIN32

  msvc {
    QMAKE_CXXFLAGS_EXCEPTIONS_ON  =   -EHs
    QMAKE_CXXFLAGS                +=  -wd4251 -wd4290 -wd4250 -wd4297 -wd4267 -wd4334
    DEFINES                       +=  BOTAN_BUILD_COMPILER_IS_MSVC \
                                      BOTAN_TARGET_OS_HAS_GMTIME_S \
                                      _SCL_SECURE_NO_WARNINGS
  } else {
    QMAKE_CFLAGS                  += -fpermissive -finline-functions -Wno-long-long
    QMAKE_CXXFLAGS                += -fpermissive -finline-functions -Wno-long-long
  }
  LIBS            +=  -ladvapi32 -luser32
}

unix:*-g++* {
  QMAKE_CFLAGS    +=  -fPIC -fpermissive -finline-functions -Wno-long-long
  QMAKE_CXXFLAGS  +=  -fPIC -fpermissive -finline-functions -Wno-long-long
}

linux*|freebsd* {
  LIBS            +=  -lrt -ldl $$QMAKE_LIBS_DYNLOAD
}
