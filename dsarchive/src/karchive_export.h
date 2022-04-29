#ifndef KARCHIVE_EXPORT_H
#define KARCHIVE_EXPORT_H

#include <QtGlobal>

#ifdef KARCHIVE_STATIC_DEFINE
#  define KARCHIVE_EXPORT
#  define KARCHIVE_NO_EXPORT
#else
#  define KARCHIVE_EXPORT     Q_DECL_EXPORT
#  define KARCHIVE_NO_EXPORT  Q_DECL_HIDDEN
#endif

#ifndef KARCHIVE_DEPRECATED
#  define KARCHIVE_DEPRECATED Q_DECL_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef KARCHIVE_NO_DEPRECATED
#    define KARCHIVE_NO_DEPRECATED
#  endif
#endif

#endif