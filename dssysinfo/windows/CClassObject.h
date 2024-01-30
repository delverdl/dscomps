#ifndef CCLASSOBJECT_H
#define CCLASSOBJECT_H

#include <QVariant>

#ifdef __GNUC__
#include <windows.h>
#include <wbemidl.h>
#else
#include <Windows.h>
#include <WbemIdl.h>
#endif
#include <comdef.h>

class Q_DECL_HIDDEN CClassObject
{
  public:
                      CClassObject(IWbemClassObject* coValue = nullptr);
    ~                 CClassObject();

    void              setObject(IWbemClassObject* coValue);
    QVariant          propertyValue(QString name);
    QStringList       properties();

  private:
    IWbemClassObject* m_object;
    QVariant          msVariantToQVariant(VARIANT msVariant);

};

#endif // CCLASSOBJECT_H
