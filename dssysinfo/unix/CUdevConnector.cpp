#include "CUdevConnector.h"

#include <libudev.h>
#include <string.h>

#include <QDebug>
#include <QRegularExpression>

CUdevConnector::CUdevConnector()
  : CCommonConnector(), m_enumerate(nullptr), m_devices(nullptr)
{ qDebug() << "CUdevConnector: Connector created";
  errno = 0; m_udev = udev_new(); if (!m_udev) m_error = errno; }

CUdevConnector::~CUdevConnector()
{ releaseEnumerator(); if (m_udev) { udev_unref(m_udev); m_udev = nullptr; } }

bool CUdevConnector::isValid() const
{ return m_udev != nullptr; }

bool CUdevConnector::execQuery()
{ if (!isValid()) return false;

  bool bResult = false;

  qDebug() << "CUdevConnector: Run query";

  m_error = 0;
  releaseEnumerator();
  m_enumerate = udev_enumerate_new(m_udev);
  if  (m_enumerate)
  { errno = 0;

    bResult = udev_enumerate_add_match_subsystem(m_enumerate, m_class.toLatin1().constData()) >= 0 &&
              udev_enumerate_scan_devices(m_enumerate) >= 0;
    if (bResult)
    { errno = 0;
      m_devices = udev_enumerate_get_list_entry(m_enumerate);
      bResult = m_devices != nullptr;
      if (!bResult) m_error = errno;
    }
    else
      m_error = errno;
  }
  else
    m_error = errno;
  return bResult;
}

QVariantMap CUdevConnector::nextObject()
{ QVariantMap vm;

  if (m_devices != nullptr)
  { struct udev_device* dev;
    QString             path = udev_list_entry_get_name(m_devices);

    errno = 0;
    m_error = 0;
    if (m_condition.contains("/")) path += m_condition;
    dev = udev_device_new_from_syspath(m_udev, path.toLatin1().constData());
    if (dev)
    { struct udev_device* childdev = nullptr;

      if (m_condition == "*") childdev = udev_device_get_parent(dev);
      else if (m_condition.contains(','))
      { QStringList sl = m_condition.split(',');

        if (!sl.isEmpty())
        { char* subs = strdup(sl.first().toLatin1().constData());
          char* devt = sl.count() > 1 ? nullptr : strdup(sl.last().toLatin1().constData());

          childdev = udev_device_get_parent_with_subsystem_devtype(dev, subs, devt);
          if (devt) free(devt);
          free(subs);
        }
      }
      else childdev = dev;

      if (childdev) getDevice(childdev, vm);
      udev_device_unref(dev);
    }
    else
      m_error = errno;
    m_devices = udev_list_entry_get_next(m_devices);
  }
  return vm;
}

void CUdevConnector::releaseEnumerator()
{ if (m_enumerate)
  { udev_enumerate_unref(m_enumerate); m_enumerate = nullptr; }
  m_devices = nullptr;
}

void CUdevConnector::getDevice(struct udev_device* childdev, QVariantMap& vm)
{ struct udev_list_entry* props = udev_device_get_sysattr_list_entry(childdev),
                        * pent;
  const char*             szVal;

  //Attributes
  if (props)
  {
    udev_list_entry_foreach(pent, props)
    { const char* prname = udev_list_entry_get_name(pent);

      if (!m_properties.contains(prname)) m_properties << prname;
      szVal = udev_device_get_sysattr_value(childdev, prname);
      vm.insert(prname, QString(szVal));
    }
  }

  //Properties
  props = udev_device_get_properties_list_entry(childdev);
  if (props)
  { udev_list_entry_foreach(pent, props)
    { const char* prname = udev_list_entry_get_name(pent);

      if (!m_properties.contains(prname)) m_properties << prname;
      szVal = udev_device_get_property_value(childdev, prname);
      vm.insert(prname, QString(szVal));
    }
  }
}
