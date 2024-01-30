#ifndef CUNIX32INFO_H
#define CUNIX32INFO_H

#include <CCommonInfo.h>

#include <sys/utsname.h>

class Q_DECL_HIDDEN CUnix32Info: public CCommonInfo
{
  public:
                    CUnix32Info();
    ~               CUnix32Info();

    QString         osName() const;
    CDisk::Map      disks() const;
    QDateTime       installDate() const;
    QString         applicationDisk() const;
    CUsers          userList() const;

  private:
    struct utsname  m_uname;

    bool            currentHaveRoot() const;
    void            getBoard();

};

#endif //CUNIX32INFO_H
