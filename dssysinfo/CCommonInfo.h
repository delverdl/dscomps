#ifndef CCOMMONDATA_H
#define CCOMMONDATA_H

#include "CInformer.h"

#include <QProcessEnvironment>

#ifdef Q_OS_LINUX
class CCommonInfo;

struct SBoardProps
{
  public:
    const char* name;
    QString CCommonInfo::*field;
};
#endif

class Q_DECL_HIDDEN CCommonInfo: public CInformer
{
  public:
                          CCommonInfo();
    ~                     CCommonInfo();
    bool                  isSystem64Bits() const;
    bool                  isApplication64Bits() const;
    CTags                 networkInterfaces() const;
    QString               boardName() const;
    QString               boardVersion() const;
    QString               boardSerial() const;
    QString               boardManufacturer() const;
    QString               computerName() const;
    QString               currentUser() const;
    QString               homePath() const;

    CDisk::Map            disks() const;

  protected:

    QString               m_boardName;
    QString               m_boardVersion;
    QString               m_boardSerial;
    QString               m_boardManufacturer;
    QProcessEnvironment*  m_env;
    QString               m_home;
    QString               m_currentUser;
    QString               m_computerName;
    bool                  m_system64;
    QString               m_diskClass;

#ifdef Q_OS_LINUX
    static SBoardProps    m_boardProps[4];
#endif

    QString               readFile(const QString& f);
};

#endif // CCOMMONDATA_H

