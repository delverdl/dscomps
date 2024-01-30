#include <CSysInfo.h>

#include <QByteArray>
#include <QCoreApplication>
#include <QLibrary>
#include <QSettings>
#include <QString>
#include <QTemporaryFile>
#include <QTextCodec>
#include <QTextStream>
#include <QDir>

QTextStream co(stdout);

QTextStream& operator<<(QTextStream& s, const CDisk& d)
{ s << d.model() << " [" << d.serial() << "] " << "(" << d.device() << ")";
  return s;
}

int main(int argc, char* argv[])
{ QCoreApplication a(argc, argv);
  CSysInfo* ksi = CSysInfo::instance();
  Q_UNUSED(a);

  CConnector* cn = ksi->connector();
  QVariantMap mp;
  int         n = 1;

#ifdef Q_OS_WIN32
  cn->setClassName("Win32_BIOS");
  if (cn->execQuery())
  {
    co << "BIOS" << endl << "======================" << endl;
    mp = cn->nextObject();
    if (!mp.isEmpty() && (mp.count() == cn->properties().count()))
      co << "Name               : " << mp.value("Caption").toString()  << endl
         << "Manufacturer       : " << mp.value("Manufacturer").toString()  << endl
         << "Serial Number      : " << mp.value("SerialNumber").toString()  << endl;
  }
#else
  QString sPath = "/device";
  QString intended = "/block/";

  cn->setClassName("scsi_disk");
  cn->setCondition(sPath);
  if (cn->execQuery())
  {
    co << "DISKS" << endl << "======================" << endl;
    mp = cn->nextObject();
    if (!mp.isEmpty())
      co << "Model              : " << mp.value("model").toString() << endl
         << "Revision           : " << mp.value("rev").toString() << endl;

    sPath += intended;

    //To get related block device name in devpath + "/block/*"
    QDir        d (QString("/sys%1%2").arg(mp.value("DEVPATH").toString()).arg(intended));
    QStringList sbd = d.entryList(QDir::AllDirs | QDir::NoDotAndDotDot);

    if (!sbd.isEmpty())
    {
      intended = sbd.first();
      sPath += intended;

      cn->setCondition(sPath); //To open block device
      if (cn->execQuery())
      {
        mp = cn->nextObject();
        if (!mp.isEmpty())
          co << "Size               : " << mp.value("size").toInt() / 2 << " KiB" << endl
             << "Device             : " << mp.value("DEVNAME").toString() << endl;
      }
    }
  }
#endif
  QByteArray rndBuff;

  n = 1;
  co << endl << "RANDOM GEN" << endl << "======================" << endl;
  forever
  {
    rndBuff = ksi->randBuffer(32);
    if (!rndBuff.isEmpty())
    { co << "Random buffer " << n << "    : ";
      co << QByteArray(rndBuff, 32).toBase64();
      co << endl;
    }
    if (++n > 2) break;
  }

  CInformer* inf = ksi->informer();
  co << endl << "SYSTEM INFO" << endl << "======================" << endl;
  co << "Application disk   : " << inf->applicationDisk() << endl;
  co << "Computer name      : " << inf->computerName() << endl;
  co << "Current user       : " << inf->currentUser() << endl;
  co << "Home path          : " << inf->homePath() << endl;
  co << "Install date       : " << inf->installDate().toString() << endl;
  co << "Motherboard name   : " << inf->boardName() << endl;
  co << "Motherboard serial : " << inf->boardSerial() << endl;
  co << "Motherboard version: " << inf->boardVersion() << endl;
  co << "Motherboard manuf. : " << inf->boardManufacturer() << endl;
  co << "Operating system   : " << inf->osName() << endl;

  { CDisk::Map::const_iterator  disk;
    CDisk::Map                  disks;

    n = 1;
    co << "Disks              :" << endl;
    disks = inf->disks();
    for (disk = disks.cbegin(); disk != disks.cend(); ++disk, ++n)
      co << "          Disk ("    << n << ") : "
         << disk.value()          << endl;
  }

  { CTags::const_iterator i;
    CTags                 items;

    n = 1;
    co << "Network interfaces :" << endl;
    items = inf->networkInterfaces();

#ifdef Q_OS_WIN32
    QTextCodec*           cod = QTextCodec::codecForName("IBM 850");
#endif

    for (i = items.cbegin(); i != items.cend(); ++i, ++n)
    {
      QByteArray  fu =
#ifdef Q_OS_WIN32
          cod->fromUnicode(i.key());
#else
          i.key().toLatin1();
#endif

      printf("     Interface (%d) : %s (%s)\n",
             n, fu.data(), i.value().toLatin1().data());
    }
  }

  CUsers ul = inf->userList();

  co << "Users              :";
  foreach (const QString& usr, ul.keys())
    co << " " << usr;
  co << endl;
  return 0;
}
