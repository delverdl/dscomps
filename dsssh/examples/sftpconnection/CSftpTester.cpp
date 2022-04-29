#include "CSftpTester.h"

#include <QCoreApplication>
#include <QDir>
#include <QtDebug>
#include <QTimer>

const char* cszCpuInfoFile = "/proc/cpuinfo";

const char* cszErrors[] =
{ "SshNoError", "SshSocketError", "SshTimeoutError", "SshProtocolError",
  "SshHostKeyError", "SshKeyFileError", "SshAuthenticationError",
  "SshClosedByServerError", "SshInternalError"
};

CSftpTester::CSftpTester(QObject *parent):
  QObject(parent)
{ m_params.setHost("localhost");
  m_params.setUserName("scn");
  m_params.setPassword("scn");
  m_params.setPort(22); //Default SSH port
  m_params.timeout = 30; //Seconds
  m_params.authenticationType = QSsh::SshConnectionParameters::AuthenticationTypePassword;
  //This callback is only a dummy funcion to show how to setup packets encryption
  //process, when authentication type is AuthenticationTypePublicKey
  m_params.passwordFunction = BIND_MEM_CB(&CSftpTester::passwordCallback, this);
}

void CSftpTester::start()
{ QTimer::singleShot(10, this, SLOT(getDiskName())); }

void CSftpTester::getDiskName()
{ m_cnx = QSsh::acquireConnection(m_params);
  connect(m_cnx, SIGNAL(connected()), SLOT(sshConnected()));
  connect(m_cnx, SIGNAL(disconnected()), SLOT(sshDisconnected()));
  connect(m_cnx, SIGNAL(error(QSsh::SshError)), SLOT(sshError(QSsh::SshError)));
  m_cnx->connectToHost();
}

//SSH
void CSftpTester::sshConnected()
{ qDebug() << "Connected to SSH with: " << m_params.host();

  m_ftp = m_cnx->createSftpChannel();
  connect(m_ftp.data(), SIGNAL(channelError(QString)), SLOT(sftpChannelError(QString)));
  connect(m_ftp.data(), SIGNAL(closed()), SLOT(sftpClosed()));
  connect(m_ftp.data(), SIGNAL(dataAvailable(QSsh::SftpJobId,QString)), SLOT(sftpDataAvailable(QSsh::SftpJobId,QString)));
  connect(m_ftp.data(), SIGNAL(finished(QSsh::SftpJobId,QString)), SLOT(sftpFinished(QSsh::SftpJobId,QString)));
  connect(m_ftp.data(), SIGNAL(initialized()), SLOT(sftpInitialized()));
  m_ftp->initialize();
}

void CSftpTester::sshDisconnected()
{ qDebug() << "Disonnected from: " << m_params.host(); }

void CSftpTester::sshError(QSsh::SshError se)
{ quint32       nError  = (quint32) se;
  const quint32 nLast   = (quint32) QSsh::SshInternalError;

  qCritical() << "SSH error (" << nError << "): "
              << cszErrors[nError > nLast ? nLast : nError ];
  doFinish();
}

void CSftpTester::sftpInitialized()
{ qDebug() << "SFTP initialized";
  m_lastJob = m_ftp->downloadFile(cszCpuInfoFile,
                                  QDir::currentPath() +
                                  QDir::separator() +
                                  "model_name.txt",
                                  QSsh::SftpOverwriteExisting);
  if (m_lastJob == QSsh::SftpInvalidJob)
    qCritical() << "Cannot create job for copying file!";
}

void CSftpTester::sftpChannelError(const QString &reason)
{ qDebug() << "SFTP channel error: " << reason; }

void CSftpTester::sftpClosed()
{ qDebug() << "SFTP closed";
  doFinish();
}

void CSftpTester::sftpFinished(QSsh::SftpJobId job, const QString &error)
{ Q_UNUSED(job);

  qDebug() << "Job finished: " << error;
  m_ftp->closeChannel();
}

void CSftpTester::sftpDataAvailable(QSsh::SftpJobId job, const QString &data)
{ Q_UNUSED(job);

  qDebug() << "In data: " << data;
}

void CSftpTester::finish()
{ QSsh::releaseConnection(m_cnx);
  QTimer::singleShot(1, qApp, SLOT(quit()));
}

void CSftpTester::doFinish()
{ QTimer::singleShot(10, this, SLOT(finish())); }

QString CSftpTester::passwordCallback(bool &ok)
{ ok = true;
  return "My0PassWor%d";
}
