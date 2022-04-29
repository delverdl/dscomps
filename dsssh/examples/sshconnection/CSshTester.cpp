#include "CSshTester.h"

#include <QCoreApplication>
#include <QtDebug>
#include <QTimer>

#include <sshremoteprocess.h>

const char* cszDiskNameCmd = "cat /sys/class/block/sda/device/model";

const char* cszErrors[] =
{ "SshNoError", "SshSocketError", "SshTimeoutError", "SshProtocolError",
  "SshHostKeyError", "SshKeyFileError", "SshAuthenticationError",
  "SshClosedByServerError", "SshInternalError"
};

CSshTester::CSshTester(QObject *parent):
  QObject(parent)
{ m_params.setHost("localhost");
  m_params.setUserName("scn");
  m_params.setPassword("scn");
  m_params.setPort(22); //Default SSH port
  m_params.timeout = 30; //Seconds
  m_params.authenticationType = QSsh::SshConnectionParameters::AuthenticationTypePassword;
  //This callback is only a dummy funcion to show how to setup packets encryption
  //process, when authentication type is AuthenticationTypePublicKey
  m_params.passwordFunction = BIND_MEM_CB(&CSshTester::passwordCallback, this);
}

void CSshTester::start()
{ QTimer::singleShot(10, this, SLOT(getDiskName())); }

void CSshTester::getDiskName()
{ m_cnx = QSsh::acquireConnection(m_params);
  connect(m_cnx, SIGNAL(connected()), SLOT(sshConnected()));
  connect(m_cnx, SIGNAL(disconnected()), SLOT(sshDisconnected()));
  connect(m_cnx, SIGNAL(error(QSsh::SshError)), SLOT(sshError(QSsh::SshError)));
  m_cnx->connectToHost();
}

//SSH
void CSshTester::sshConnected()
{ qDebug() << "Connected to SSH with: " << m_params.host() << endl;

  m_process = m_cnx->createRemoteProcess(cszDiskNameCmd);
  connect(m_process.data(), SIGNAL(started()), SLOT(processStarted()));
  connect(m_process.data(), SIGNAL(closed(int)), SLOT(processClosed(int)));
  connect(m_process.data(), SIGNAL(readyReadStandardError()), SLOT(processReadyReadStandardError()));
  connect(m_process.data(), SIGNAL(readyReadStandardOutput()), SLOT(processReadyReadStandardOutput()));
  m_process->start();
}

void CSshTester::sshDisconnected()
{ qDebug() << "Disonnected from: " << m_params.host() << endl; }

void CSshTester::sshError(QSsh::SshError se)
{ quint32       nError  = (quint32) se;
  const quint32 nLast   = (quint32) QSsh::SshInternalError;

  qCritical() << "SSH error (" << nError << "): "
              << cszErrors[nError > nLast ? nLast : nError ]
              << endl;
  doFinish();
}

void CSshTester::processStarted()
{ qDebug() << "Remote program started" << endl; }

void CSshTester::processReadyReadStandardOutput()
{ qDebug() << "PROGRAM (stdout): " << m_process->readAllStandardOutput(); }

void CSshTester::processReadyReadStandardError()
{ qDebug() << "PROGRAM (stderr): " << m_process->readAllStandardError(); }

void CSshTester::processClosed(int exitStatus)
{ qDebug() << "Remote program exited with code: " << exitStatus << endl;
  doFinish();
}

void CSshTester::finish()
{ QSsh::releaseConnection(m_cnx);
  QTimer::singleShot(1, qApp, SLOT(quit()));
}

void CSshTester::doFinish()
{ QTimer::singleShot(10, this, SLOT(finish())); }

QString CSshTester::passwordCallback(bool &ok)
{ ok = true;
  return "My0PassWor%d";
}
