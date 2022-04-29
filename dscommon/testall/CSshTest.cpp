#include "CSshTest.h"
#include "CTestWindow.h"
#include "ui_CTestWindow.h"

#include <QMessageBox>
#include <QPlainTextEdit>
#include <sshkeycreationdialog.h>
#include <sshremoteprocess.h>

void enable(QWidget* w, bool e = true)
{ w->setEnabled(e); }

void disable(QWidget* w)
{ enable(w, false); }

CSshTest::CSshTest(QObject *parent)
  : QObject(parent), m_main(qobject_cast<CTestWindow*>(parent)), m_cnx(nullptr)
{ }

CSshTest::~CSshTest()
{ if (m_cnx) finish(); }

bool CSshTest::isConnected()
{ return m_cnx && m_cnx->state() == QSsh::SshConnection::Connected;  }

void CSshTest::init()
{ Ui::CTestWindow* w = m_main->ui;

  m_params.timeout            = 30;     //Seconds
  m_params.setPort(22);     //Default SSH port
  m_params.authenticationType =
      QSsh::SshConnectionParameters::AuthenticationTypePassword;

  connect(w->pbSshDialog, SIGNAL(clicked(bool)), SLOT(buttonWantDialog()));
  connect(w->pbSshConnect, SIGNAL(clicked(bool)), SLOT(buttonConnect()));
  connect(w->pbSshDisconnect, SIGNAL(clicked(bool)), SLOT(finish()));
  connect(w->leSshHost, SIGNAL(textEdited(QString)), SLOT(editModified(QString)));
  connect(w->leSshUser, SIGNAL(textEdited(QString)), SLOT(editModified(QString)));

  w->pteSshConsole->setUndoRedoEnabled(false);
  connect(w->leSshCommand, SIGNAL(returnPressed()), SLOT(editReturnPressed()));

  connect(w->leSshHost, SIGNAL(returnPressed()), w->leSshUser, SLOT(setFocus()));
  connect(w->leSshUser, SIGNAL(returnPressed()), w->leSshPassword, SLOT(setFocus()));
  connect(w->leSshPassword, SIGNAL(returnPressed()), SLOT(buttonConnect()));
}

void CSshTest::sshConnected()
{ Ui::CTestWindow* w = m_main->ui;

  enable(w->leSshCommand);
  enable(w->pteSshConsole);
  enable(w->pbSshDisconnect);
  disable(w->leSshHost);
  disable(w->leSshPassword);
  disable(w->leSshUser);
  disable(w->sbxSshPort);
  disable(w->sbxSshTimeout);

  w->leSshCommand->setFocus();
}

void CSshTest::sshDisconnected()
{ Ui::CTestWindow* w = m_main->ui;

  disable(w->leSshCommand);
  disable(w->pteSshConsole);
  enable(w->pbSshConnect);
  enable(w->leSshHost);
  enable(w->leSshPassword);
  enable(w->leSshUser);
  enable(w->sbxSshPort);
  enable(w->sbxSshTimeout);

  w->leSshHost->setFocus();
  w->pteSshConsole->clear();
}

static const char* cszErrors[] =
{ "", "Ssh Socket Error", "Ssh Timeout Error", "Ssh Protocol Error",
  "Ssh Host Key Error", "Ssh Key File Error", "Ssh Authentication Error",
  "Ssh Closed By Server Error", "Ssh Internal Error"
};

void CSshTest::sshError(QSsh::SshError se)
{ if (se == QSsh::SshNoError) return;
  else
  { quint32       nError  = static_cast<quint32>(se);
    const quint32 nLast   = static_cast<quint32>(QSsh::SshInternalError);
    QString       s;
    QTextStream   so(&s);

    so << "SSH error (" << nError << "): "
       << cszErrors[nError > nLast ? nLast : nError ];

    QMessageBox::critical(m_main, "Error", s);
  }
}

void CSshTest::processStarted()
{ m_main->ui->leSshCommand->clear();
}

void cleanUpString(QString& s)
{ s.replace("\\t", "\t");
  s.replace("\\b", "\b");
  s.replace("\\n", "\n");
  s.replace("\\r", "\r");
  s.replace("\\v", "\v");
  s.replace("\\\"", "\"");
}

void CSshTest::processReadyReadStandardOutput()
{ QString s;

  s = m_process->readAllStandardOutput();
  cleanUpString(s);
  m_main->ui->pteSshConsole->setPlainText(s);
}

void CSshTest::processReadyReadStandardError()
{ QString s;

  s = m_process->readAllStandardError();
  cleanUpString(s);
  m_main->ui->pteSshConsole->setPlainText(s);
}

void CSshTest::processClosed(int exitStatus)
{ Q_UNUSED(exitStatus);
  enable(m_main->ui->leSshCommand);
  m_main->ui->leSshCommand->setFocus();
}

void CSshTest::finish()
{ Ui::CTestWindow* w = m_main->ui;

  disable(w->pbSshDisconnect);
  m_cnx->disconnectFromHost();
  QSsh::releaseConnection(m_cnx);
  m_cnx = nullptr;
}

void CSshTest::buttonWantDialog()
{ QSsh::SshKeyCreationDialog* dlg = new QSsh::SshKeyCreationDialog(m_main);

  dlg->exec();
  delete dlg;
}

void CSshTest::buttonConnect()
{ Ui::CTestWindow* w = m_main->ui;

  disable(w->pbSshConnect);

  m_params.setHost(w->leSshHost->text());
  m_params.setPassword(w->leSshPassword->text());
  m_params.setUserName(w->leSshUser->text());
  m_params.timeout = w->sbxSshTimeout->value();
  m_params.setPort(static_cast<quint16>(w->sbxSshPort->value()));
  m_cnx = QSsh::acquireConnection(m_params);
  connect(m_cnx, SIGNAL(connected()), SLOT(sshConnected()));
  connect(m_cnx, SIGNAL(disconnected()), SLOT(sshDisconnected()));
  connect(m_cnx, SIGNAL(error(QSsh::SshError)), SLOT(sshError(QSsh::SshError)));
  m_cnx->connectToHost();
}

void CSshTest::editModified(const QString& s)
{ Q_UNUSED(s);
  Ui::CTestWindow* w = m_main->ui;

  enable(w->pbSshConnect, !w->leSshHost->text().isEmpty() && !w->leSshUser->text().isEmpty());
}

void CSshTest::editReturnPressed()
{ QLineEdit* le = m_main->ui->leSshCommand;
  QPlainTextEdit* pte = m_main->ui->pteSshConsole;

  if (le->text().isEmpty()) return;
  pte->clear();
  disable(le);
  m_process = m_cnx->createRemoteProcess(le->text().toLatin1());
  connect(m_process.data(), SIGNAL(started()), SLOT(processStarted()));
  connect(m_process.data(), SIGNAL(closed(int)), SLOT(processClosed(int)));
  connect(m_process.data(), SIGNAL(readyReadStandardError()), SLOT(processReadyReadStandardError()));
  connect(m_process.data(), SIGNAL(readyReadStandardOutput()), SLOT(processReadyReadStandardOutput()));
  m_process->start();
}
