#ifndef CUDEVCONNECTOR_H
#define CUDEVCONNECTOR_H

#include <CCommonConnector.h>

class Q_DECL_HIDDEN CUdevConnector :
    public CCommonConnector
{
  public:
                            CUdevConnector();
    ~                       CUdevConnector();

    bool                    isValid() const;
    bool                    execQuery();
    QVariantMap             nextObject();

  private:
    struct udev*            m_udev;
    struct udev_enumerate*  m_enumerate;
    struct udev_list_entry* m_devices;

    void                    releaseEnumerator();
    void                    getDevice(struct udev_device* childdev, QVariantMap& vm);

};


#endif // CUDEVCONNECTOR_H
