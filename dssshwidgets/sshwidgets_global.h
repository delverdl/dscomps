
#pragma once

#include "ssh_global.h"

#if defined(QSSHWIDGETS_LIBRARY)
#  define QSSHWIDGETS_EXPORT Q_DECL_EXPORT
#else
#  define QSSHWIDGETS_EXPORT Q_DECL_IMPORT
#endif
