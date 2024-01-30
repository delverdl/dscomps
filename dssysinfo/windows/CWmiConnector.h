#ifndef CWMICONNECTOR_H
#define CWMICONNECTOR_H

#include <wchar.h>
#ifdef __GNUC__
#include <wbemidl.h>
#else
#include <WbemIdl.h>
#endif
#include <comdef.h>

#include <CCommonConnector.h>

class Q_DECL_HIDDEN CWmiConnector:
    public CCommonConnector
{
  public:
                          CWmiConnector(const QString& nameSpace = QString("root\\cimv2"));
    ~                     CWmiConnector();

    bool                  isValid() const;
    bool                  execQuery();
    QVariantMap           nextObject();

  private:
    IWbemLocator*         m_locator;
    IWbemServices*        m_services;
    IEnumWbemClassObject* m_enumerator;
    bool                  m_hasCOM, m_hasLocator, m_hasServices;

    void                  releaseEnum();
};

#endif // CWMICONNECTOR_H
