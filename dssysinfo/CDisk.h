#ifndef CDISK_H
#define CDISK_H

#include <QVariantMap>

#include "dstypes.h"

/**
 * @brief Disk's basic information class.
 *
 * This class will allow user to get a system's hard drive basic information; its
 * layout should be obtained through a CConnector class instance, for example,
 * Win32_DiskPartition WMI class should be good for such purpose.
 */
class CDisk
{
  public:

    /**
     * @brief Disks map.
     *
     * This type is used to define disks in a system, and its used by CInformer class.
     * The key of every map entry is the physical device name, and thus the value is
     * a CDisk static reference.
     *
     * @see CInformer
     */
    typedef QMap<QString, CDisk> Map;

    /**
     * @brief Empty or invalid disk instance constructor.
     */
    CDisk(): m_size(0), m_valid(false) {}

    /**
     * @brief Disk instance constructor using input data.
     *
     * This method will set up a CDisk instance with a device's name, a serial number,
     * a size and a valid disk model.
     *
     * @param d Disk physical name
     * @param m Disk model
     * @param s Disk serial number
     * @param z Disk size in bytes
     *
     * @see CInformer
     */
    CDisk(const QString& d, const QString& m, const QString& s, qint64 z)
      : m_device(d), m_model(m), m_serial(s), m_size(z), m_valid(true)
    {  }

    /**
     * @brief Disk instance's contructor from a properties map.
     *
     * This method will set up a CDisk instance using @ref CConnector "classes connector"
     * for a @ref CConnector::execQuery "query"; thus every disk in system's got through
     * the @ref CConnector::nextObject "next device" method, which returns a
     * @c QVarianMap set of properties and values. The former is internally used within
     * CInformer class.
     *
     * @param vm Disk properties map.
     *
     * @see CInformer
     * @see CConnector
     */
    CDisk(const QVariantMap& vm)
      :
#ifdef Q_OS_WIN32
        m_device(QString("\\\\.\\PhysicalDrive%1").arg(vm.value("Index").toInt())),
        m_model(vm.value("Model").toString()),
        m_serial(vm.value("SerialNumber").toString()),
        m_size(vm.value("Size").toLongLong()),
        m_valid(vm.contains("Index") && vm.contains("FirmwareRevision") &&
                vm.contains("InterfaceType"))
#else
        m_device(vm.value("DEVNAME").toString()),
        m_model(vm.value("ID_MODEL").toString()),
        m_serial(vm.value("ID_SERIAL_SHORT").toString()),
        m_size(vm.value("size").toLongLong() / 2 * 1024),
        m_valid(vm.value("DEVTYPE").toString() == "disk" && !vm.contains("partition"))
#endif
    {  }

    /**
     * @brief Disk instance copy constructor.
     *
     * @param other Another static reference to a disk's instance.
     */
    CDisk(const CDisk& other)
    { operator=(other); }

    /**
     * @brief Validity check.
     * @return Disk instance validity.
     */
    bool isValid() const
    {
      //Some flash drives have invalid or empty serial number, so this
      //check could be an issue
      return m_valid && !m_device.isEmpty() && !m_serial.isEmpty() && !m_model.isEmpty();
    }

    /**
     * @brief Disk device name.
     * @return Physical disk path name.
     */
    QString device() const  { return m_device; }

    /**
     * @brief Disk model string.
     * @return Physical disk model name.
     */
    QString model() const  { return m_model; }

    /**
     * @brief Disk serial number.
     * @return Physical disk serial number.
     */
    QString serial() const  { return m_serial; }

    /**
     * @brief Disk's size.
     * @return Physical disk size in bytes.
     */
    qint64  size() const  { return m_size; }
    
    CDisk&  operator=(const CDisk& other)
    { m_device = other.m_device; m_model = other.m_model; m_serial = other.m_serial;
      m_size = other.m_size; m_valid = other.m_valid;
      return *this;
    }

  private:
    //Members
    QString m_device;
    QString m_model;
    QString m_serial;
    qint64  m_size;
    bool    m_valid;

};

#endif // CDISK_H

