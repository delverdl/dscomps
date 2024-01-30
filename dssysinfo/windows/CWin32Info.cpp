#include "CWin32Info.h"

#include <CSysInfo_p.h>

#include <assert.h>
#include <Windows.h>
#include <LM.h>

#include <QCoreApplication>
#include <QSettings>

HANDLE openPath(LPCWSTR szPath, DWORD dwAccess)
{ return CreateFile(szPath,
                    dwAccess,
                    FILE_SHARE_READ | FILE_SHARE_WRITE,
                    nullptr,
                    OPEN_EXISTING,
                    0,
                    nullptr);
}

BOOL getVolumeAccessPath(WCHAR cDrive, LPWSTR szPath)
{ WCHAR cDriveLetter;

  cDriveLetter = towupper(cDrive);
  wcscpy(szPath, L"\\\\.\\X:");
  if (cDriveLetter < L'A' || cDriveLetter > L'Z') return FALSE;
  szPath[4] = cDriveLetter; //Set device path
  return TRUE;
}

BOOL pathDeviceNumber(LPCWSTR szPath, PSTORAGE_DEVICE_NUMBER sdt)
{ HANDLE hVolume;
  DWORD dwBytesReturned = 0;
  BOOL bRet = FALSE;

  hVolume = openPath(szPath, 0);
  if (hVolume != INVALID_HANDLE_VALUE)
  { bRet = DeviceIoControl(hVolume, IOCTL_STORAGE_GET_DEVICE_NUMBER, nullptr, 0, sdt,
                           sizeof(STORAGE_DEVICE_NUMBER), &dwBytesReturned, nullptr);
    CloseHandle(hVolume);
  }
  return bRet;
}

////2
DWORD getDriveDeviceNumber(WCHAR cDrive)
{ WCHAR szVolumeAccessPath[8];
  DWORD nDiskNumber = static_cast<DWORD>(1);
  STORAGE_DEVICE_NUMBER sdt;

  if (getVolumeAccessPath(cDrive, szVolumeAccessPath) &&
      pathDeviceNumber(szVolumeAccessPath, &sdt))
    nDiskNumber = sdt.DeviceNumber;
  return nDiskNumber;
}

CWin32Info::CWin32Info()
  : CCommonInfo()
{ m_computerName =  m_env->value("COMPUTERNAME").toLower();
  m_currentUser =  m_env->value("USERNAME").toLower();
  m_home = m_env->value("HOMEDRIVE") + m_env->value("HOMEPATH");
  getSystemBits();
  getBoard();
}

CWin32Info::~CWin32Info()
{  }

QString CWin32Info::osName() const
{ QString sResult, sCsd;
  QSettings conf("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft" \
                "\\Windows NT\\CurrentVersion", QSettings::NativeFormat);

  sResult = conf.value("ProductName").toString();
  sCsd = conf.value("CSDVersion").toString();
  if (!sCsd.isEmpty()) sResult += QString(" (%1)").arg(sCsd);
  return sResult;
}

CDisk::Map CWin32Info::disks() const
{ const_cast<QString&>(m_diskClass) = "Win32_DiskDrive";
  return CCommonInfo::disks();
}

#if (QT_VERSION >= QT_VERSION_CHECK(5, 10, 0))
#define secsSinceEpoc()   toSecsSinceEpoch()
#define fromSecsSince(t)  fromSecsSinceEpoch(t)
#else
#define secsSinceEpoc()   toMSecsSinceEpoch()/1000
#define fromSecsSince(t)  fromMSecsSinceEpoch(t*1000)
#endif

QDateTime CWin32Info::installDate() const
{ QSettings conf("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft" \
                 "\\Windows NT\\CurrentVersion", QSettings::NativeFormat);

  return QDateTime::fromSecsSince(
        conf.value("InstallDate",
                   QDateTime::currentDateTime().secsSinceEpoc()).toUInt());
}

QString CWin32Info::applicationDisk() const
{ QString sAppDir = QCoreApplication::applicationDirPath();

  if (!sAppDir.isEmpty())
  { WCHAR lwc = sAppDir.unicode()[0].unicode();
    DWORD dwDrive = getDriveDeviceNumber(lwc);

    return QString("\\\\.\\PhysicalDrive%1").arg(dwDrive);
  }
  return QString();
}

bool currentHaveRoot()
{ QSettings conf("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft" \
                 "\\Windows NT\\CurrentVersion", QSettings::NativeFormat);

  conf.setValue("Win32Info", 33452);
  conf.sync();
  if (conf.value("Win32Info").toInt() == 33452)
  { conf.remove("Win32Info");
    return true;
  }
  else
    return false;
}

CUsers CWin32Info::userList() const
{ CUsers          lUsers;
  bool            croot = false;
  bool            iscurrent;
  LPUSER_INFO_1   pBuf = nullptr;
  LPUSER_INFO_1   pTmpBuf;
  DWORD           dwLevel = 1;
  DWORD           dwPrefMaxLen = MAX_PREFERRED_LENGTH;
  DWORD           dwEntriesRead = 0;
  DWORD           dwTotalEntries = 0;
  DWORD           dwResumeHandle = 0;
  DWORD           i;
  NET_API_STATUS  nStatus;
  LPTSTR          pszServerName = nullptr;
  QString         sName;

  do
  { nStatus = NetUserEnum(static_cast<LPCWSTR>(pszServerName),
                          dwLevel,
                          FILTER_NORMAL_ACCOUNT, // global users
                          reinterpret_cast<LPBYTE*>(&pBuf),
                          dwPrefMaxLen,
                          &dwEntriesRead,
                          &dwTotalEntries,
                          &dwResumeHandle);
    if ((nStatus == NERR_Success) || (nStatus == ERROR_MORE_DATA))
    { if ((pTmpBuf = pBuf) != nullptr)
      { for (i = 0; (i < dwEntriesRead); i++)
        { assert(pTmpBuf != nullptr);
          if (pTmpBuf == nullptr)
          { fprintf(stderr, "An access violation has occurred\n");
            break;
          }
          sName.setUnicode(reinterpret_cast<const QChar*>(pTmpBuf->usri1_name),
                           static_cast<int>(wcslen(pTmpBuf->usri1_name)));
          iscurrent = m_currentUser == sName;
          croot = iscurrent ? currentHaveRoot() : pTmpBuf->usri1_priv == USER_PRIV_ADMIN;
          lUsers.insert(sName, croot);
          pTmpBuf++;
        }
      }
    }
    else fprintf(stderr, "A system error has occurred: %d\n", static_cast<int>(nStatus));
    if (pBuf != nullptr) { NetApiBufferFree(pBuf); pBuf = nullptr; }
  }
  while (nStatus == ERROR_MORE_DATA); // end do
  if (pBuf != nullptr) NetApiBufferFree(pBuf);
  return lUsers;
}

void CWin32Info::getSystemBits()
{
#ifdef Q_OS_WIN64
  m_system64 = true;
#else
  typedef BOOL (WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);

  LPFN_ISWOW64PROCESS fnIsWow64Process;

  BOOL bIsWow64 = FALSE;

  fnIsWow64Process = reinterpret_cast<LPFN_ISWOW64PROCESS>((void *) (GetProcAddress(GetModuleHandle(TEXT("kernel32")), "IsWow64Process")));
  if(NULL != fnIsWow64Process) fnIsWow64Process(GetCurrentProcess(), &bIsWow64);
  m_system64 = bIsWow64 == TRUE;
#endif
}

void CWin32Info::getBoard()
{ CConnector* cn = CSysInfo::connector();

  cn->setClassName("Win32_BaseBoard");
  if (cn->execQuery())
  { QVariantMap mp;

    mp = cn->nextObject();
    if (mp.isEmpty() || (mp.count() != cn->properties().count())) return;
    m_boardName = mp.value("Product").toString();
    m_boardVersion = mp.value("Version").toString();
    m_boardSerial = mp.value("SerialNumber").toString();
    m_boardManufacturer = mp.value("Manufacturer").toString();
  }
}

CConnector* CSysInfo::connector()
{ if (!m_connector) m_connector = new CWmiConnector;
  return m_connector;
}

HCRYPTPROV CSysInfoPrivate::m_cryptProvider = 0;

CSysInfoPrivate::CSysInfoPrivate(CSysInfo* q)
{ initInstances<CWin32Info>(q); }

CSysInfoPrivate::~CSysInfoPrivate()
{ releaseInstances<CWin32Info>(); }

void CSysInfoPrivate::getCryptProvider()
{ if (m_cryptProvider != 0) return; /*Do nothing if crypto provider is open*/

  LPCWSTR cszCont = L"DSKeys";

  if (!CryptAcquireContext(&m_cryptProvider, cszCont, nullptr, PROV_RSA_FULL, 0) &&
      GetLastError() == static_cast<DWORD>(NTE_BAD_KEYSET) )
    CryptAcquireContext(&m_cryptProvider, cszCont, nullptr, PROV_RSA_FULL, CRYPT_NEWKEYSET);
}

void CSysInfoPrivate::releaseCryptProvider()
{ /*Release crypto provider used memory*/
  if (m_cryptProvider != 0)
  { CryptReleaseContext(m_cryptProvider, 0);
    m_cryptProvider = 0;
  }
}

bool CSysInfoPrivate::randGetBuffer(int nLen)
{ getCryptProvider(); //Initialize crypto provider
  if (!m_cryptProvider) return false;
  return CryptGenRandom(m_cryptProvider, static_cast<DWORD>(nLen),
                        reinterpret_cast<BYTE*>(m_randBuffer.data())) == TRUE;
}
