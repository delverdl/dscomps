#ifndef CABSTRACTMEDIA
#define CABSTRACTMEDIA

#include <QtCore/QString>
#include <QtCore/QIODevice>

#include "DeviceErrors.h"

#include <callback.hpp>

class CAbstractMedia
{
  public:

    typedef       util::Callback<void (DeviceStatus)> CbDeviceStatus;

    virtual ~     CAbstractMedia() {}

    virtual void  openMedia(const QString& sDevice) = 0;
    virtual void  openMedia(QIODevice* bus) = 0;
    virtual void  closeMedia() = 0;

    virtual void  setStatusReport(CbDeviceStatus ds) = 0;
};

#endif // CABSTRACTMEDIA

