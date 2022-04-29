#include "CTestWindow.h"
#include "ui_CTestWindow.h"

#include "CCryptTest.h"
#include "CPropertiesTest.h"
#include "CSshTest.h"
#include "CWidgetsTest.h"

#include <AppUtils>
#include <CPosItem>
#include <CSysInfo.h>
#include <K7Zip>
#include <KTar>
#include <KZip>

#include <QApplication>
#include <QCloseEvent>
#include <QMessageBox>
#include <QTimer>
#include <QTextCodec>
#include <QDir>
#include <QPluginLoader>
#include <QFileDialog>

CTestWindow::CTestWindow(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::CTestWindow),
  m_printer(nullptr)
{ //GUI setup
  ui->setupUi(this);
  connect(ui->pbTestPrint, &QPushButton::clicked, this, &CTestWindow::testPrintStart);

  //System information
  CSysInfo *ksi = CSysInfo::instance();

  { CInformer*  inf = ksi->informer();
    QString     s   = QString("Motherboard: %1 %2, serial: %3")
                      .arg(inf->boardManufacturer(),
                           inf->boardName(),
                           inf->boardSerial());

    ui->lblSysBoard->setText(s);
    ui->lblSysDisk->setText(QString("Application disk: %1").arg(inf->applicationDisk()));
    ui->lblSysOs->setText(QString("OS: %1").arg(inf->osName()));
    ui->lblSysPc->setText(QString("PC name: %1").arg(inf->computerName()));

    QString sNics = "Network interfaces:\n";
    QMapIterator<QString, QString>  i(inf->networkInterfaces()) ;

    while (i.hasNext())
    { i.next();

      sNics += QString("\tName: %1 MAC: %2\n").arg(i.key(), i.value().toLatin1().data());
    }
    ui->lblSysNic->setText(sNics);

    delete ksi;
  }

  //DsCrypt
  m_cry = new CCryptTest(this);
  m_cry->init();

  //DsSsh
  m_ssh = new CSshTest(this);
  m_ssh->init();

  //Qwt & wwWidgets
  m_wgt = new CWidgetsTest(this);
  m_wgt->init();

  //DsPBrowser
  //Enqueue initialization due to main window widgets creation process
  m_props = new CPropertiesTest(this);
  QTimer::singleShot(10, m_props, SLOT(init()));
}

CTestWindow::~CTestWindow()
{ releaseResources();
  delete ui;
}

void CTestWindow::on_pbClose_clicked()
{ QTimer::singleShot(5, this, SLOT(close())); }

void CTestWindow::on_pbDecompress_clicked()
{ QString sFile = QFileDialog::getOpenFileName(
                    this, "Open compressed file...",
                    QDir::homePath(),
                    tr("Archives (*.tar.gz *.tar.bz2 *.tar.xz *.zip *.7z *.7zip"));
  QFileInfo fi(sFile);

  if (fi.exists())
  { QString   sListing;
    KArchive* ar;

    if (fi.suffix() == "7z" || fi.suffix() == "7zip")
      ar = new K7Zip(sFile);
    else if (fi.suffix() == "zip")
      ar = new KZip(sFile);
    else
      ar = new KTar(sFile);

    if (ar->open(QIODevice::ReadOnly))
    { auto rootDir = ar->directory();
      auto rootEntries = rootDir->entries();

      for (const QString& entry : rootEntries)
      { auto kent = rootDir->entry(entry);
        QString sTemp = kent->date().toString(Qt::ISODate);

        if (!sTemp.isEmpty()) sListing += sTemp;
        else sListing += QDateTime::currentDateTime().toString(Qt::ISODate);
        sListing += QString(" ");
        if (kent->isFile())
        { auto kfil = rootDir->file(entry);

          sListing += QString("%1 ").arg(kfil->size(), 11);
        } else
          sListing += QString(12, QChar(' '));
        sListing += QString("%1\n").arg(kent->name());
      }
    }
    if (!sListing.isEmpty())
    { QDialog* dlg = new QDialog;
      QGridLayout* glo = new QGridLayout(dlg);
      QTextEdit* te = new QTextEdit(dlg);

      te->setFont(QFontDatabase::systemFont(QFontDatabase::FixedFont));
      te->setFontWeight(14);
      te->setText(sListing);
      glo->addWidget(te);
      dlg->exec();
      delete dlg;
    }
    delete ar;
  }
}

void CTestWindow::testPrintStart()
{ QDir    pluginsDir = QDir(qApp->applicationDirPath());
  QString sSave;

#if defined(Q_OS_MAC)
  if (pluginsDir.dirName() == "MacOS")
  { pluginsDir.cdUp(); pluginsDir.cdUp(); pluginsDir.cdUp(); }
#else
  if (pluginsDir.dirName().toLower() == "debug" ||
      pluginsDir.dirName().toLower() == "release" ||
      pluginsDir.dirName().toLower() == "bin") pluginsDir.cdUp();
#endif
  pluginsDir.cd("plugins");

  if (pluginsDir.exists())
  { QStringList files = pluginsDir.entryList(QDir::Files);

    sSave = QDir::currentPath();
    QDir::setCurrent(pluginsDir.canonicalPath());
    for (const QString& sFile: files)
    { QPluginLoader pl(sFile);
      QObject* obj = pl.instance();

      if (obj)
      { m_printer = qobject_cast<CAbstractPrinter*>(obj);
        if (m_printer) break;
      }
    }
    QDir::setCurrent(sSave);
  }
  if (!m_printer)
  { QMessageBox::critical(this, "Error", "Error loading printer plugin");
    return;
  }
  else QTimer::singleShot(10, this, SLOT(testOpenPrinter()));
}

void CTestWindow::testOpenPrinter()
{ m_printer->setStatusReport(BIND_MEM_CB(&CTestWindow::printerStatus, this));
  m_printer->setPrintDone(BIND_MEM_CB(&CTestWindow::printDone, this));
  m_printer->openMedia("COM3");
}

void CTestWindow::testDoPrint()
{ CPosItem::List toPrint;

  toPrint << new CPosItemLineFeed
          << new CPosItemImage(":/ds.png")
          << new CPosItemLineFeed
          << new CPosItemText("Prueba de impresión de texto", true, false, Qt::AlignCenter)
          << new CPosItemLineFeed
          << new CPosItemText("Mes\tCol1\tCol2\tCol3")
          << new CPosItemLineFeed
          << new CPosItemText("Enero\t5002\t403\t380")
          << new CPosItemLineFeed
          << new CPosItemText("Febrero\t667\t704\t99212")
          << new CPosItemLineFeed
          << new CPosItemText("Marzo\t12292\t122\t7534")
          << new CPosItemLineFeed(3)
          << new CPosItemBarcode("1234567890123")
          << new CPosItemLineFeed(8)
             ;

  m_printer->printDocument(toPrint);
}

void CTestWindow::testFinishPrint()
{ if (m_printer) m_printer->closeMedia();
  release(m_printer);
}

void CTestWindow::closeEvent(QCloseEvent *event)
{ event->accept(); }

void CTestWindow::releaseResources()
{ release(m_cry);
  release(m_ssh);
  release(m_props);
  release(m_wgt);
  release(m_printer);
}

void CTestWindow::printerStatus(DeviceStatus ds)
{ if (ds == dsNoError) QTimer::singleShot(0, this, SLOT(testDoPrint()));
  else QTimer::singleShot(0, this, SLOT(testFinishPrint()));
}

void CTestWindow::printDone(bool b)
{ Q_UNUSED(b); QTimer::singleShot(0, this, SLOT(testFinishPrint())); }
