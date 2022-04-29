#include "CAppLogger.h"

#include <QCoreApplication>
#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QStandardPaths>

QFile*  CAppLogger::fLog = nullptr;

CAppLogger::CAppLogger()
{  }

CAppLogger::~CAppLogger()
{  }

void CAppLogger::activate()
{
  QString sConfigFile = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
  QDir    dConfig(sConfigFile);

  //Create application configuration directory if not exists
  if (!dConfig.exists()) dConfig.mkpath(sConfigFile);
  sConfigFile += "/application.log";
  fLog = new QFile(sConfigFile);
  fLog->open(QIODevice::Append);
  qInstallMessageHandler(messageHandler);

  QString s1 = QCoreApplication::applicationName(),
          s2 = QCoreApplication::organizationName();

  qDebug() << ":::appname: " << s1 << " :::apporg : " << s2 << " Log opened in " << sConfigFile;
}

void CAppLogger::messageHandler(QtMsgType type, const QMessageLogContext& context,
                                const QString& msg)
{ QString sOut;

  // Start with date-time
  sOut = QDateTime::currentDateTime().toString("[yyyy-MM-dd hh:mm:ss] ");
  // By type determine to what level belongs message
  switch (type)
  { case QtInfoMsg:     sOut += "(INF) "; break;
    case QtDebugMsg:    sOut += "(DBG) "; break;
    case QtWarningMsg:  sOut += "(WRN) "; break;
    case QtCriticalMsg: sOut += "(CRT) "; break;
    case QtFatalMsg:    sOut += "(FTL) "; break;
  }
  // Add category
  sOut += QString("%1: %2\n").arg(context.category, msg);

  //Put string out to file and Standard Error stream.
  fprintf(stderr, "%s", sOut.toLatin1().data()); fflush(stderr);
  if (fLog->isOpen()) { fLog->write(sOut.toLatin1()); fLog->flush(); }
}
