#ifndef KTYPES_H
#define KTYPES_H

#include <QDateTime>
#include <QFile>
#include <QHash>
#include <QMap>
#include <QString>

#ifdef Q_OS_UNIX
#include <sys/time.h>
#endif

#include <sys/types.h>

/** @def KSYSINFOSHARED_EXPORT
 *
 * @brief Exportation/importation macro
 *
 * This macro is internally used by the library to provide Windows exported symbols, and
 * so their inclusion for a proper application usage.
 *
 */
#if !defined(DSSYS_INFO_STATIC)
# if defined(DSSYS_INFO_LIBRARY)
#   define KSYSINFOSHARED_EXPORT Q_DECL_EXPORT
# else
#   define KSYSINFOSHARED_EXPORT Q_DECL_IMPORT
# endif
#else
# define KSYSINFOSHARED_EXPORT
#endif

/**
 * @brief Strings dictionary.
 *
 * This type is used for @ref CInformer::networkInterfaces "network interfaces" map.
 * Having the NIC name as key and its MAC as the value.
 *
 * @see CInformer
 */
typedef QMap<QString, QString>  CTags;

/**
 * @brief String to boolean hash-table-based dictionary.
 *
 * This type is used for @ref CInformer::userList method, to get system's available user
 * names and its root/administrator access bit. This is that if an user has its bit set
 * to @b true, then he is a system administrator, otherwise this bit would be set to
 * @b false.
 *
 * @see CInformer
 */
typedef QHash<QString, bool>    CUsers;

/** @mainpage DSSysInfo library API
 *
 * This is the system information library API, is has been tested in Windows 10 and
 * Ubuntu Linux 18.04. User only need to use one header file to completely have access to
 * library's functionality; CSysInfo class is the one exported to have access to both
 * @ref CConnector "devices connector" and @ref CInformer "system information" interfaces;
 * and thus @ref CSysInfo::randBuffer "access" a random buffer filling method. You cannot
 * have multiple instances of this class; it's only @ref CSysInfo::instance "allowed" one
 * per process, and it's explained in the following code snippet
 *
 * @verbatim
 * # In PRO file
 *
 * CONFIG += dssysinfo
 *
 * @endverbatim
 *
 * @code
 *
 * #include <CSysInfo>
 *
 * //...
 *
 * CSysInfo* m_ksysinfo = CSysInfo::instance();
 *
 * //...
 *
 * @endcode
 *
 * @anchor si_references
 * There's a good <a href="http://www.signal11.us/oss/udev/">tutorial</a> for using UDEV.
 * and you should look at the
 * <a href="https://msdn.microsoft.com/en-us/library/aa393964(v=vs.85).aspx">Win32 WMI</a>
 * classes to know about how to query them and their properties. Most of windows CIM
 * classes are provided in Windows desktop apps -> System Administration -> WMI Providers
 * -> CIMWin32 WMI Providers ->
 * <a href="https://msdn.microsoft.com/en-us/library/aa394388(v=vs.85).aspx">Win32
 * Provider</a> web page.
 *
 * @todo An aditional source code for such systems like OSX, BSD*, AIX, HPUX, etc could
 * be added providing an usage extension to the library.
 *
 * @author Delver Domingo. Montevideo 2019. delverdl@gmail.com
 * @date 2017-05-03
 * @copyright GNU LGPL version 3.
 */

#endif // KTYPES_H

