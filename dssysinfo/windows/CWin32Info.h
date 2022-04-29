#ifndef CWIN32INFO_H
#define CWIN32INFO_H

#include <CCommonInfo.h>

#include "CWmiConnector.h"

class Q_DECL_HIDDEN CWin32Info: public CCommonInfo
{
  public:
                    CWin32Info();
    ~               CWin32Info();

    QString         osName() const;
    CDisk::Map      disks() const;
    QDateTime       installDate() const;
    QString         applicationDisk() const;
    CUsers          userList() const;

  private:
    void            getSystemBits();
    void            getBoard();
};

#endif // CWIN32INFO_H

