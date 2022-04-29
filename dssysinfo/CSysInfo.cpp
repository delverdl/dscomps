#include "CSysInfo_p.h"

#include <QDebug>
#include <QThread>

#include <time.h>

CSysInfo::~CSysInfo()
{ d_ptr->releaseCryptProvider(); delete d_ptr; m_instance = nullptr; }

CSysInfo* CSysInfo::m_instance = nullptr;
CConnector* CSysInfo::m_connector = nullptr;

CSysInfo* CSysInfo::instance()
{ if (!m_instance) m_instance = new CSysInfo;
  return m_instance;
}

CInformer* CSysInfo::informer()
{ Q_D(CSysInfo); return d->m_informer; }

QByteArray CSysInfo::randBuffer(int nSize)
{ Q_D(CSysInfo);

  d->m_randBuffer.clear();
  if (nSize > 0)
  { d->m_randBuffer.resize(nSize);
    if (!d->randGetBuffer(nSize))
    { QThread::usleep(1);
      srand(static_cast<unsigned int>(time(nullptr))); /*initialize simple generator*/
      for (int i = 0; i < nSize; i++)
        d->m_randBuffer[i] = static_cast<char>((rand() % 0xff));
    }
  }
  return d->m_randBuffer;
}

CSysInfo::CSysInfo()
  : d_ptr(new CSysInfoPrivate(this)) { }

CSysInfo::CSysInfo(const CSysInfo& other)
{ operator=(other); }

CSysInfo& CSysInfo::operator=(const CSysInfo& other)
{ d_ptr = other.d_ptr;
  return *this;
}
