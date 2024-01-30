#ifndef CSYSINFO_H
#define CSYSINFO_H

#include "CConnector.h"
#include "CInformer.h"

class CSysInfoPrivate;

/**
 * @brief The system information class
 *
 * This class provide access to operating system's information via CInformer interface;
 * you could @ref CSysInfo::connector "get" extra system information via CConnector
 * interface. Besides, you can @ref CSysInfo::randBuffer retrieve a randomized buffer in a
 * byte array. The <a href="index.html">main page</a> of DSSysInfo library help shows
 * how to create an instance of this class.
 */
class KSYSINFOSHARED_EXPORT CSysInfo
{
  public:
    /**
     * @brief Class destructor
     *
     * This will free all resources used by this class
     */
    ~CSysInfo();

    /**
     * @brief Class' instance
     *
     * This method will create a new object of CSysInfo type; it won't create several
     * instances of this class, because it'll return previous object instance
     *
     * @return An object of CSysInfo type
     */
    static CSysInfo*    instance();

    /**
     * @brief Get system's connector
     *
     * This will return an object instance of CConnector interface; you can use it
     * to query Operating System's hardware and/or software objects. See
     * @ref si_references "here".
     *
     * @return Connector's instance
     */
    static CConnector*  connector();

    /**
     * @brief System information instance
     *
     * This method will return an object instance of CInformer interface, for some
     * specific Operating System's informations.
     *
     * @return System information instance
     */
    CInformer*          informer();

    /**
     * @brief Get randomized buffer
     *
     * You can use this function to get \c nSize ramdom bytes buffer.
     *
     * @param nSize Requested size of resulting buffer. If it's less or equal to zero
     * then the buffer will be empty.
     *
     * @return Radom buffer of requested size.
     */
    QByteArray          randBuffer(int nSize);

  private:
                        CSysInfo();

    //Two instances share the same pointer that's why this operator and associated copy
    //constructor are private; it'd be an error to use any of them. They're merely declared
    //and implemented for avoiding destructor declaration warning (in C++11): it's a rule
    //that if you declare a destructor, in specific cases, you must declare a copy
    //constructor and operator

                        CSysInfo(const CSysInfo& other);
    CSysInfo&           operator=(const CSysInfo& other);

    CSysInfoPrivate*    d_ptr;
    Q_DECLARE_PRIVATE   (CSysInfo)

    /**
     * @brief Static instance of the class for a single object access. If this object
     * is not null then \ref instance "associated" method will return it, otherwise
     * it'll create a new instance of CSysInfo.
     */
    static CSysInfo*    m_instance;
    static CConnector*  m_connector;

};

#endif // CSYSINFO_H
