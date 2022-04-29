#ifndef CINFORMER_H
#define CINFORMER_H

#include "dstypes.h"
#include "CDisk.h"

/**
 * @brief Simple system information class
 *
 * This class will allow user to get some sort of system basic information, such as if
 * the @ref CInformer::isSystem64Bits "system is 64 or 32 bits", the operating system
 * @ref CInformer::osName "name", the system's available users
 * @ref CInformer::osName "list" and such.
 *
 *
 */
class CInformer
{
  public:

    /**
     * @brief Instance virtual destructor
     */
    virtual ~           CInformer();

    /*Operating system*/
    /**
     * @brief Check if OS is 64 bits or not.
     * @return Returns @b true if OS is 64 bits, otherwise it'll returns false.
     */
    virtual bool        isSystem64Bits() const = 0;

    /**
     * @brief Check if current application is 64 bits or not.
     * @return Returns @b true if application is 64 bits, otherwise it'll returns false.
     */
    virtual bool        isApplication64Bits() const = 0;

    /**
     * @brief Get OS name.
     * @return Returns a string showing the complete OS name.
     */
    virtual QString     osName() const = 0;

    /**
     * @brief Get OS installation date.
     * @return Returns current operating system's install date.
     * @note In case of Linux it should be the start of installation procedure.
     */
    virtual QDateTime   installDate() const = 0;

    /**
     * @brief List of users.
     * @return Returns hashed dictionary of user names present in system, where the
     * @c key is the user name and the @c value is a @b bool flag indicating if user
     * has administrative privileges; that is, for instance, you can write to
     * @c HKEY_LOCAL_MACHINE windows registry key or you can read from /proc/kcore
     * (which is complete RAM memory) in Linux.
     */
    virtual CUsers      userList() const = 0;

    /**
     * @brief Get computer name.
     * @return Returns computer's name.
     */
    virtual QString     computerName() const = 0;

    /**
     * @brief Get current user name.
     * @return Returns the current user name string.
     */
    virtual QString     currentUser() const = 0;

    /**
     * @brief Get home directory.
     * @return Returns user's home directory as for QDir::homePath() method.
     */
    virtual QString     homePath() const = 0;

    /*Hardware*/
    /**
     * @brief Get physical disks list.
     * @return Returns a dictionary of physical disks installed where the @c key is
     * the physical drive path and the @c value is a CDisk static reference.
     */
    virtual CDisk::Map  disks() const = 0;

    /**
     * @brief Get list of network interfaces availables.
     * @return Returns a string dictionary with the @c key referred as the NIC name and
     * the @c value is the MAC address of such NIC.
     */
    virtual CTags       networkInterfaces() const = 0;

    /**
     * @brief Get application disk.
     * @return Returns the physical drive path where current application instance is run.
     */
    virtual QString     applicationDisk() const = 0;

    /**
     * @brief Get motherboard's serial.
     * @return Returns a string indicating mainboard's model name.
     * @note In Linux, application must be ran in root user space to query
     * this value. Nevertheless, if you run (without quotes)
     * "sudo chmod +s /usr/sbin/dmidecode"
     * it would be possible to get this value from an unprivileged user.
     */
    virtual QString     boardName() const = 0;

    /**
     * @brief Get motherboard's version.
     * @return Returns a string indicating mainboard's version numbers.
     * @note In Linux, application must be ran in root user space to query
     * this value. Nevertheless, if you run (without quotes)
     * "sudo chmod +s /usr/sbin/dmidecode"
     * it would be possible to get this value from an unprivileged user.
     */
    virtual QString     boardVersion() const = 0;

    /**
     * @brief Get motherboard's serial.
     * @return Returns a string indicating mainboard's serial.
     * @note In Linux, application must be ran in root user space to query
     * this value. Nevertheless, if you run (without quotes)
     * "sudo chmod +s /usr/sbin/dmidecode"
     * it would be possible to get this value from an unprivileged user.
     */
    virtual QString     boardSerial() const = 0; /*Required root access in Linux*/

    /**
     * @brief Get motherboard's manufacturer name.
     * @return Returns a string indicating mainboard's manufaturer name.
     * @note In Linux, application must be ran in root user space to query
     * this value. Nevertheless, if you run (without quotes)
     * "sudo chmod +s /usr/sbin/dmidecode"
     * it would be possible to get this value from an unprivileged user.
     */
    virtual QString     boardManufacturer() const = 0;
};

inline CInformer::~CInformer() {}

#endif // CINFORMER_H

