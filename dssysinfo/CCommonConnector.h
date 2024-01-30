#ifndef CCOMMONCONNECTOR_H
#define CCOMMONCONNECTOR_H

#include "CConnector.h"

class Q_DECL_HIDDEN CCommonConnector: public CConnector
{
  public:
    CCommonConnector();

    void        setClassName(const QString& value);
    QString     className() const;
    void        setProperties(const QStringList& value);
    QStringList properties() const;
    void        setCondition(const QString& value);
    QString     condition() const;
    long        lastError() const;

  protected:
    long        m_error;
    QString     m_class, m_condition;
    QStringList m_properties;

    int         duplicateIndex(QString s, QStringList l, int index);

};

#endif // CCOMMONCONNECTOR_H
