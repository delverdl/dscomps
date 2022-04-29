#include "CCommonInfo.h"
#include "CConnector.h"
#include "CSysInfo.h"

#include <QDebug>
#include <QNetworkInterface>

#ifdef Q_OS_LINUX
SBoardProps CCommonInfo::m_boardProps[4] =
{
  {"manufacturer",  &CCommonInfo::m_boardManufacturer},
  {"product-name",  &CCommonInfo::m_boardName},
  {"serial-number", &CCommonInfo::m_boardSerial},
  {"version",       &CCommonInfo::m_boardVersion},
};
#endif

CCommonInfo::CCommonInfo()
  : m_env(new QProcessEnvironment(QProcessEnvironment::systemEnvironment())),
    m_diskClass("unknown")
{  }

CCommonInfo::~CCommonInfo()
{ delete m_env; }

bool CCommonInfo::isSystem64Bits() const
{ return m_system64; }

bool CCommonInfo::isApplication64Bits() const
{ return (sizeof(void*) == 8) ; }

CTags CCommonInfo::networkInterfaces() const
{ QList<QNetworkInterface> nics = QNetworkInterface::allInterfaces();
  CTags       tResult;
  QString     sh, sn;
  QStringList tkn;
  int         zcn;
  int         nx;
  bool        ok;

  foreach (const QNetworkInterface& nic, nics)
  { sh = nic.hardwareAddress();
    tkn = sh.split(":");
    zcn = 0;
    ok = false;
    foreach (sn, tkn)
    { nx = sn.toInt(&ok, 16);
      //Must be a valid number and if zeroes count is more the normal
      //part count for a MAC address then it is invalid
      if (!ok || nx || ++zcn > 5) break;
    }
    sn = nic.humanReadableName();
    if (!ok || zcn > 5 || sn.contains("virtualbox", Qt::CaseInsensitive)) continue;
    tResult.insert(sn, sh);
  }
  return tResult;
}

QString CCommonInfo::boardName() const
{ return m_boardName; }

QString CCommonInfo::boardVersion() const
{ return m_boardVersion; }

QString CCommonInfo::boardSerial() const
{ return m_boardSerial; }

QString CCommonInfo::boardManufacturer() const
{ return m_boardManufacturer; }

QString CCommonInfo::computerName() const
{ return m_computerName; }

QString CCommonInfo::currentUser() const
{ return m_currentUser; }

QString CCommonInfo::homePath() const
{ return m_home; }

CDisk::Map CCommonInfo::disks() const
{ CDisk::Map result;
  CConnector* cn;

  cn = CSysInfo::connector();
  qDebug() << "CCommonInfo: Set class name -> " << hex << reinterpret_cast<uint64_t>(cn);
  cn->setClassName(m_diskClass);
  qDebug() << "CCommonInfo: Query disks";
  if (cn->execQuery())
  { QVariantMap mp;

    forever
    { mp = cn->nextObject();
      if (mp.isEmpty()) break;

      CDisk d(mp);

      if (d.isValid()) result.insert(d.device(), d);
    }
  }
  return result;
}

QString CCommonInfo::readFile(const QString& f)
{ QFile in(f);

  if (in.open(QIODevice::ReadOnly)) return in.readAll();
  else return QString();
}
