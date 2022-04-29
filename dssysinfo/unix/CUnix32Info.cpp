#include "CUdevConnector.h"
#include "CUnix32Info.h"

#include <CSysInfo_p.h>

#include <QCoreApplication>
#include <QDir>
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QProcess>
#include <QRegularExpression>
#include <QSettings>

#include <errno.h>
#include <grp.h>
#include <mntent.h>
#include <pwd.h>
#include <sys/stat.h>

CTags mountPoints()
{ FILE*           entries = setmntent("/etc/mtab", "r");
  CTags           mounts;
  struct mntent*  me;

  forever
  { me = getmntent(entries);
    if (!me) break;
    mounts.insert(me->mnt_fsname, me->mnt_dir);
  }
  return mounts;
}

CUnix32Info::CUnix32Info()
  : CCommonInfo()
{ if (uname(&m_uname) != 0) perror("Error initializing information data");
  m_currentUser =  m_env->value("USER").toLower();
  m_home = m_env->value("HOME");
  m_system64 = QString(m_uname.machine).contains("64");
  m_computerName = readFile("/etc/hostname").trimmed();
  getBoard();
}

CUnix32Info::~CUnix32Info()
{  }

QString CUnix32Info::osName() const
{ const char* key = "/etc/os-release";
  QSettings   cfg(key, QSettings::NativeFormat);
  QString     sOut;

  if (!QFile::exists(key)) sOut = QString("%1 %2")
                                  .arg(m_uname.sysname)
                                  .arg(m_uname.version);
  else sOut = QString("%1 %2").arg(cfg.value("NAME").toString())
              .arg(cfg.value("VERSION").toString());
  return sOut;
}

CDisk::Map CUnix32Info::disks() const
{ const_cast<QString&>(m_diskClass) = "block";
  qDebug() << "CUnix32Info: Getting disks";
  return CCommonInfo::disks();
}

QDateTime CUnix32Info::installDate() const
{ /*Assuming there's no system update, just a fresh installation*/
  QFileInfo f(
      #ifdef Q_OS_MAC
        "/private/var/db/.AppleSetupDone"
      #else
        /*This might be used in hpux, aix, or other unixes*/
        "/lost+found"
      #endif
        );

  if (f.exists()) return f.created();
  else return QDateTime::currentDateTime();
}

QString findFsName(const CTags& mnts, const QString& path)
{ QString               found;
  int                   nMaxLen = 0;
  CTags::const_iterator i;

  for (i = mnts.constBegin(); i != mnts.constEnd(); ++i)
  { if (path.contains(i.value())) /*Mount dir in queried path?*/
    { if (i.value().length() > nMaxLen)
      { nMaxLen = i.value().length();
        found = i.key();
      }
    }
  }
  return found;
}

QString CUnix32Info::applicationDisk() const
{ QString     sAppDir = QCoreApplication::applicationDirPath();
  QString     sResult;
  CTags       mnts = mountPoints();
  struct stat sInfo;

  forever
  { sAppDir = findFsName(mnts, sAppDir);
    if (!stat(sAppDir.toLatin1().constData(), &sInfo))
    { if (S_ISBLK(sInfo.st_mode))
      { sAppDir.chop(1);
        sResult = sAppDir;
        break;
      }
    }
    else
    { perror("Cannot get application disk");
      break;
    }
  }
  return sResult;
}

CUsers CUnix32Info::userList() const
{ struct passwd*  user;
  bool            croot;
  CUsers          lUsers;

  setpwent();
  forever
  { croot = false;
    user = getpwent();
    if (!user) break;
    if (m_currentUser == QString(user->pw_name)) croot = currentHaveRoot();
    lUsers.insert(user->pw_name, user->pw_uid == 0 || croot);
  }
  endpwent();
  return lUsers;
}

bool CUnix32Info::currentHaveRoot() const
{ QByteArray  baRand(CSysInfo::instance()->randBuffer(8));
  QFile       f(QString("/root/root.test.%1").arg(QString(baRand.toBase64())));

  if (f.open(QIODevice::WriteOnly))
  { f.close();
    f.remove();
    return true;
  }
  return false;
}

void CUnix32Info::getBoard()
{ // DMIDECODE must be abailable to run from unprivileged user
  // chmod +s /usr/sbin/dmidecode
  for (int i  = 0; i < 4; i++)
  { QProcess dd;

    dd.start(QString("/usr/sbin/dmidecode -s system-%1").arg(m_boardProps[i].name));
    if (dd.waitForFinished())
    { QString sResult = dd.readAll();

      this->*(m_boardProps[i].field) = sResult.trimmed();
    }
  }
}

CConnector* CSysInfo::connector()
{ qDebug() << "CSysInfo: Creating connector";
  if (!m_connector) m_connector = new CUdevConnector;
  return m_connector;
}

QFile* CSysInfoPrivate::m_cryptProvider = nullptr;

CSysInfoPrivate::CSysInfoPrivate(CSysInfo* q)
{ initInstances<CUnix32Info>(q); }

CSysInfoPrivate::~CSysInfoPrivate()
{ releaseInstances<CUnix32Info>(); }

void CSysInfoPrivate::getCryptProvider()
{ if (m_cryptProvider) return;
  m_cryptProvider = new QFile("/dev/urandom");
  if (m_cryptProvider && !m_cryptProvider->open(QIODevice::ReadOnly))
    releaseCryptProvider();
}

void CSysInfoPrivate::releaseCryptProvider()
{ if (m_cryptProvider)
  { delete m_cryptProvider;
    m_cryptProvider = 0;
  }
}

bool CSysInfoPrivate::randGetBuffer(int nLen)
{ getCryptProvider();
  if (!m_cryptProvider) return false;
  return m_cryptProvider->read(m_randBuffer.data(), nLen) == nLen;
}
