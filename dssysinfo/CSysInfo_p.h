#ifndef CSYSINFOPRIVATE_H
#define CSYSINFOPRIVATE_H

#include "CSysInfo.h"

#ifdef Q_OS_WIN32
  #ifdef __GNUC__
    #include <windows.h>
  #else
    #include <Windows.h>
  #endif
  #include <wincrypt.h>
#endif

class Q_DECL_HIDDEN CSysInfoPrivate
{
    Q_DECLARE_PUBLIC(CSysInfo)

  public:
    CSysInfoPrivate(CSysInfo* q);
    ~CSysInfoPrivate();

    CSysInfo*         q_ptr;
    CInformer*        m_informer;
    QByteArray        m_randBuffer;

    static
#ifdef Q_OS_WIN32
      HCRYPTPROV
#else
      QFile*
#endif
                      m_cryptProvider;

    void              getCryptProvider();
    void              releaseCryptProvider();
    bool              randGetBuffer(int nLen);

    template <class I>
    void              releaseInstances()
    { I* i = dynamic_cast<I*>(m_informer);

      delete i;
      m_informer = nullptr;
    }

    template <class I>
    void              initInstances(CSysInfo* q)
    { q_ptr = q;
      m_informer = new I;
    }
};

#endif
