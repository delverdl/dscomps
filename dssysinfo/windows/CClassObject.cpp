#include "CClassObject.h"

CClassObject::CClassObject(IWbemClassObject* coValue)
  : m_object(coValue)
{ }

CClassObject::~CClassObject()
{ m_object->Release(); }

void CClassObject::setObject(IWbemClassObject* coValue)
{ if (m_object) m_object->Release();
  m_object = coValue;
}

QVariant CClassObject::msVariantToQVariant(VARIANT msVariant)
{ QVariant vResult;
  switch(msVariant.vt)
  { case VT_BSTR  :
    case VT_LPSTR :
    case VT_LPWSTR:
      { QString str(reinterpret_cast<QChar*>(msVariant.bstrVal),
                    static_cast<int>(wcslen(msVariant.bstrVal)));
        if (str.length() && str.at(0).isPrint())
          vResult = QVariant(str);
      }
      break;
    case VT_I1    :
    case VT_UI1   : vResult = QVariant(msVariant.cVal); break;
    case VT_BOOL  :
    case VT_I2    :
    case VT_UI2   : vResult = QVariant(msVariant.uiVal); break;
    case VT_I4    :
    case VT_UI4   : vResult = QVariant(msVariant.uintVal); break;
    case VT_I8    :
    case VT_UI8   : vResult = QVariant(msVariant.ullVal); break;
    case VT_R4    : vResult = QVariant(msVariant.fltVal); break;
    case VT_R8    : vResult = QVariant(msVariant.dblVal); break;
  };
  return vResult;
}

QVariant CClassObject::propertyValue(QString name)
{ VARIANT vtProp;
  QVariant vResult;
  LPCWSTR lpcw = reinterpret_cast<LPCWSTR>(name.unicode()) ;

  if (SUCCEEDED(m_object->Get(lpcw, 0, &vtProp, nullptr, nullptr)))
  { vResult = msVariantToQVariant(vtProp);
    if (vtProp.vt >= VT_I2) ::VariantClear(&vtProp);
  }
  return vResult;
}

bool printable(const QString& s)
{ foreach (const QChar& ch, s)
    if (!ch.isPrint()) return false;
  return true;
}

QStringList CClassObject::properties()
{ QStringList lResult;
  SAFEARRAY*  list = nullptr;

  if (SUCCEEDED(m_object->GetNames(nullptr, WBEM_FLAG_ALWAYS, nullptr, &list)))
  { BSTR* names = reinterpret_cast<BSTR*>(list->pvData) ;
    long  uBound = 0;
    long  n = 0;

    SafeArrayGetUBound(list, 1, &uBound);
    forever
    { QString str(reinterpret_cast<QChar*>(*names),
                  static_cast<int>(wcslen(*names)));

      if (!str.isEmpty() && printable(str)) lResult << str;
      ++(names);
      if (++n > uBound) break;
    }
  }
  return lResult;
}
