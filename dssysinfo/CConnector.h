#ifndef CCONNECTOR_H
#define CCONNECTOR_H

#include <QString>
#include <QStringList>
#include <QVariant>

/**
 * @brief System's classes connector
 *
 * This class works like a querying system, where you should
 * @ref  CConnector::setClassName "set the class name" and the
 * @ref  CConnector::setProperties "properties" you
 * wish to match for the class; using a @ref CConnector::setCondition "condition" for
 * additional matching criteria.
 *
 * @see <a href="index.html">Main page</a>
 * @see CInformer class.
 */
class CConnector
{
  public:
    /**
     * @brief Instance virtual destructor
     */
    virtual ~CConnector();

    /**
     * @brief Set the system's class name to query for
     *
     * You should use this method to set the system class name to query its information
     * for. In windows it could be, for example,
     * <a href="https://msdn.microsoft.com/en-us/library/aa394072(v=vs.85).aspx">
     * Win32_BaseBoard</a> to query for motherboard information. In Linux it could be
     * @c block to query for block devices, or in a more complex example take a look at
     * following code snipet; using "scsi_disk" class and paths conditionals, in order
     * to query for physical drives managed with @c scsi_disk shared object kernel driver.
     *
     * @anchor class_query_example
     * @code
     * QString sPath = "/device";
     * QString intended = "/block/";
     *
     * cn->setClassName("scsi_disk");
     * cn->setCondition(sPath);
     * if (cn->execQuery())
     * {
     *   co << "DISKS" << endl << "======================" << endl;
     *   mp = cn->nextObject();
     *   if (!mp.isEmpty())
     *     co << "Model              : " << mp.value("model").toString() << endl
     *        << "Revision           : " << mp.value("rev").toString() << endl;
     *
     *   sPath += intended;
     *
     *   //To get related block device name in devpath + "/block/.+"
     *   QDir        d (QString("/sys%1%2").arg(mp.value("DEVPATH").toString()).arg(intended));
     *   QStringList sbd = d.entryList(QDir::AllDirs | QDir::NoDotAndDotDot);
     *
     *   if (!sbd.isEmpty())
     *   {
     *     intended = sbd.first();
     *     sPath += intended;
     *
     *     cn->setCondition(sPath); //To open block device
     *     if (cn->execQuery())
     *     {
     *       mp = cn->nextObject();
     *       if (!mp.isEmpty())
     *         co << "Size               : " << mp.value("size").toInt() / 2 << " KiB"
     *            << endl
     *            << "Device             : " << mp.value("DEVNAME").toString()
     *            << endl;
     *     }
     *   }
     * }
     * @endcode
     *
     * @param value The class name to query for
     */
    virtual void          setClassName(const QString& value) = 0;

    /**
     * @brief Class name set to be queried for.
     * @return Returns a string representing the class name to be queried for.
     */
    virtual QString       className() const = 0;

    /**
     * @brief Set the list of properties for a query.
     *
     * This list is matched against the actual class properties; thus unexisting
     * properties are erased from the original @c value set if they ain't found in
     * selected @ref setClassName "class".
     *
     * @param value List of properties to match in class.
     *
     * @see setClassName
     * @see className
     * @see properties
     */
    virtual void          setProperties(const QStringList& value) = 0;

    /**
     * @brief Properties to be searched.
     *
     * @return Returns a string list representing the class properties to be queried for.
     *
     * @note This list may be different from the original ones @ref setProperties "set"
     * after @ref execQuery "executing" the query.
     *
     * @see setProperties
     */
    virtual QStringList   properties() const = 0;

    /**
     * @brief Set condition for the query.
     *
     * This condition is an expression like the @c WHERE clause in SQL language in
     * case of Windows (see the
     * <a href="https://msdn.microsoft.com/en-us/library/aa392902(v=vs.85).aspx">WQL</a>
     * querying reference). However, for Linux it'd be the path inside the class to be
     * queried for (see @ref class_query_example "this" example), if it has an slash
     * ("/"), or ir could be a two tokens separated a comma to query device's subsystem
     * and device type in that order, e.g., if you @ref setClassName "set" the class name
     * as @c "scsi_disk", the subsystem could be @c usb and the device type could be
     * @c usb_device, so this condition string should be "usb,usb_device"; then you'll
     * @ref execQuery "query" for the USB holding device entry of a disk. If the disk
     * is an USB flash drive, then you'll get access to the USB device holding properties,
     * i.e.: it's serial number. So when you query @ref nextObject "the object properties"
     * one of them should be @c "serial", for the USB flash drive serial number in former
     * example. Besides, if this condition is an asterisk "*" then
     * @ref nextObject "object" properties are for device's parent class.
     *
     * @param value Query condition.
     *
     * @see condition
     */
    virtual void          setCondition(const QString& value) = 0;

    /**
     * @brief Condition for the query.
     * @return Gets the current query condition.
     *
     * @see setCondition
     */
    virtual QString       condition() const = 0;

    /**
     * @brief Last error number
     *
     * Use this method to get previous action's error; for any Operating System a null
     * error means that there's no problem at all. Unixes error codes are expressed
     * in errno.h and Windows error codes are expressed in Windows.h, and their meaning
     * are very different.
     *
     * @return Last error number
     *
     * @see isValid
     */
    virtual long          lastError() const = 0;

    /**
     * @brief Gets connector validity.
     *
     * You should use this function to validate instance's proper usage; if its result
     * is @b false, then you should check the @ref lastError "last error", and then
     * take specific actions according to the error number returned; besides, you can't
     * @ref execQuery "execute" any query with this instance. The @ref lastError "error"
     * may be due to the lack of memory resources, but in case of Windows it may be
     * because the user has initialized OLE by hand elsewhere in application; this is an
     * atomic operation and should only take place once per process, using the OLE
     * functions
     * <a href="https://msdn.microsoft.com/en-us/library/windows/desktop/ms695279(v=vs.85).aspx">
     * CoInitializeEx</a> and
     * <a href="https://msdn.microsoft.com/en-us/library/windows/desktop/ms693736(v=vs.85).aspx">
     * CoInitialzeSecurity</a>.
     *
     * @return This returns @b true if instance's valid, @b false otherwise.
     *
     * @see lastError
     */
    virtual bool          isValid() const = 0;

    /**
     * @brief Run query for selected class.
     *
     * This method should be used to execute the query for the @ref setClassName "class"
     * you've set. Additionaly the @ref setCondition "condition" and/or the
     * @ref setProperties "properties" you could possibly want to find out are also taken
     * into consideration for the search.
     *
     * If an error is is found during the query execution, then the function will return
     * @b false and lastError will return the appropriated error code. On the other hand,
     * you can't run this method (and it'll automatically return @b false) if instance
     * ain't @ref isValid "valid".
     *
     * @return Returns @b true if query was successfuly executed, @b false otherwise.
     *
     * @see isValid
     * @see lastError
     * @see @ref class_query_example "This" example.
     */
    virtual bool          execQuery() = 0;

    /**
     * @brief Get next object properties map.
     *
     * This method allows user to get a dictionary of @ref setProperties "desired" or
     * available properties for current object/device in @ref setClassName "requested"
     * class; taking into consideration the @ref setCondition "conditions" met. Every
     * item is a pair of @c key and @c value, where the key is the property name and the
     * value is what it's worth. @ref class_query_example "This" example shows how to use
     * the method.
     *
     * @return Current object properties and values dictionary.
     */
    virtual QVariantMap   nextObject() = 0;

};

inline CConnector::~CConnector() {}

#endif // CCONNECTOR_H

