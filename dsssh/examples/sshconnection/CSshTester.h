#ifndef CSSHTESTER_H
#define CSSHTESTER_H

#include <QObject>

#include <sshconnection.h>
#include <sshconnectionmanager.h>

class CSshTester: public QObject
{
    Q_OBJECT

  public:
    explicit                                CSshTester(QObject *parent);

    void                                    start();

  private slots:
    void                                    getDiskName();

    //SSH
    void                                    sshConnected();
    void                                    sshDisconnected();
    void                                    sshError(QSsh::SshError se);

    //Remote process
    void                                    processStarted();
    void                                    processReadyReadStandardOutput();
    void                                    processReadyReadStandardError();
    void                                    processClosed(int exitStatus);

    //Utility
    void                                    finish();

  private:
    QSsh::SshConnection*                    m_cnx;
    QSsh::SshConnectionParameters           m_params;
    QSharedPointer<QSsh::SshRemoteProcess>  m_process;

    void                                    doFinish();
    QString                                 passwordCallback(bool &ok);
};


#endif // CSSHTESTER_H
