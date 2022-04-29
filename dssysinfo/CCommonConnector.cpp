#include "CCommonConnector.h"

CCommonConnector::CCommonConnector()
  : m_error(0), m_class("Invalid")
{ }

void CCommonConnector::setClassName(const QString& value)
{ if (!isValid()) return;
  m_condition.clear();
  m_class = value;
}

QString CCommonConnector::className() const
{ return m_class; }

void CCommonConnector::setProperties(const QStringList& value)
{ if (!isValid()) return;
  m_properties = value;
  for (int i = 0, n = 0; i < m_properties.count(); i++)
  { n = duplicateIndex(m_properties[i], m_properties, i);
    if (n >= 0) { m_properties.removeAt(n); if (n < i) i--; }
  }
}

QStringList CCommonConnector::properties() const
{ return m_properties; }

void CCommonConnector::setCondition(const QString& value)
{ if (!isValid()) return; m_condition = value; }

QString CCommonConnector::condition() const
{ return m_condition; }

long CCommonConnector::lastError() const
{ return m_error; }

int CCommonConnector::duplicateIndex(QString s, QStringList l, int index)
{ for (int i = 0; i < l.count(); i++)
  { if (i == index) continue;
    if (l[i].toLower() == s.toLower()) return i;
  }
  return -1;
}
