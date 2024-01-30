#include "CWmiConnector.h"

#ifdef __GNUC__
#include <windows.h>
#else
#include <Windows.h>
#endif
#include "CClassObject.h"

#if defined(__GNUC__) && __GNUC__ < 5
  const CLSID CLSID_WbemLocator = {0x4590F811, 0x1D3A, 0x11D0, {0x89, 0x1F, 0, 0xAA, 0, 0x4B, 0x2E, 0x24}};
#endif

CWmiConnector::CWmiConnector(const QString& nameSpace)
  : CCommonConnector(), m_hasCOM(false), m_hasLocator(false), m_hasServices(false)
{ BSTR bzServer;

  m_locator = nullptr;
  m_enumerator = nullptr;
  m_services = nullptr;
  m_error = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
  if (m_error != S_OK && m_error != S_FALSE /*Already called*/ &&
      m_error != RPC_E_CHANGED_MODE /*Called with different parameters*/) return;
  m_error = CoInitializeSecurity(nullptr, -1, nullptr, nullptr, RPC_C_AUTHN_LEVEL_DEFAULT,
                                 RPC_C_IMP_LEVEL_IMPERSONATE, nullptr, EOAC_NONE, nullptr);
  if (m_error != S_OK && m_error != RPC_E_TOO_LATE /*Already called*/) return;
  m_hasCOM = true;
  m_error = CoCreateInstance(CLSID_WbemLocator, nullptr, CLSCTX_INPROC_SERVER,
                             IID_IWbemLocator, reinterpret_cast<LPVOID *>(&m_locator));
  if (FAILED(m_error)) return;
  m_hasLocator = true;
  bzServer = ::SysAllocString(reinterpret_cast<const OLECHAR*>(nameSpace.unicode()));
  m_error = m_locator->ConnectServer(bzServer, nullptr, nullptr, nullptr, 0,
                                     nullptr, nullptr, &m_services);
  if (SUCCEEDED(m_error))
  { m_error = CoSetProxyBlanket(m_services, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, nullptr,
                                RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, nullptr,
                                EOAC_NONE);
    if (FAILED(m_error)) m_services->Release();
    else m_hasServices = true;
  }
  ::SysFreeString(bzServer);
}

CWmiConnector::~CWmiConnector()
{ releaseEnum();
  if (m_hasServices) m_services->Release();
  if (m_hasLocator) m_locator->Release();
  if (m_hasCOM) CoUninitialize();
}

bool CWmiConnector::isValid() const
{ return m_hasCOM && m_hasLocator && m_hasServices; }

const OLECHAR cszQuery[] = OLESTR("WQL");

bool CWmiConnector::execQuery()
{ if (!isValid()) return false;

  releaseEnum();
  if (!m_condition.isEmpty() && (m_condition.left(1) != " ")) m_condition.prepend(" ");

  bool        bResult = false;
  QString     sTemp = "SELECT * FROM " + m_class + m_condition;
  const BSTR  bzQuery = ::SysAllocString(reinterpret_cast<const OLECHAR*>(sTemp.unicode()));

  m_properties.clear(); //Clear previous properies
  m_error = m_services->ExecQuery(const_cast<BSTR>(cszQuery), bzQuery, //Run query
                                  WBEM_FLAG_BIDIRECTIONAL | WBEM_FLAG_RETURN_IMMEDIATELY,
                                  nullptr, &m_enumerator);
  ::SysFreeString(bzQuery);
  if (SUCCEEDED(m_error)) bResult = true;
  else releaseEnum(); //Release enumerator on error
  return bResult;
}

QVariantMap CWmiConnector::nextObject()
{ if (!isValid() || !m_enumerator) return QVariantMap();
  CClassObject*     dsObject;
  IWbemClassObject* iwObject;
  ULONG             uReturn = 0;
  QVariantMap       vm;

  m_enumerator->Next(static_cast<LONG>(WBEM_INFINITE), 1, &iwObject, &uReturn);
  if (uReturn != 0)
  { dsObject = new CClassObject(iwObject);
    if (m_properties.isEmpty()) m_properties = dsObject->properties();
    foreach (const QString& sProperty, m_properties)
      vm.insert(sProperty, dsObject->propertyValue(sProperty));
    delete dsObject;
  }
  return vm;
}

void CWmiConnector::releaseEnum()
{ if (m_enumerator)
  { m_enumerator->Release();
    m_enumerator = nullptr;
  }
}
