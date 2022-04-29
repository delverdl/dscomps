#ifndef CSFTPTESTER_H
#define CSFTPTESTER_H

#include <QObject>

#include <sftpchannel.h>
#include <sshconnection.h>
#include <sshconnectionmanager.h>

class CSftpTester: public QObject
{
    Q_OBJECT

  public:
    explicit                                CSftpTester(QObject *parent);

    void                                    start();

  private slots:
    void                                    getDiskName();

    //SSH
    void                                    sshConnected();
    void                                    sshDisconnected();
    void                                    sshError(QSsh::SshError se);

    //SFTP
    void                                    sftpInitialized();
    void                                    sftpChannelError(const QString &reason);
    void                                    sftpClosed();
    void                                    sftpFinished(QSsh::SftpJobId job, const QString &error = QString());
    void                                    sftpDataAvailable(QSsh::SftpJobId job, const QString &data);

    //Utility
    void                                    finish();

  private:
    QSsh::SshConnection*                    m_cnx;
    QSsh::SshConnectionParameters           m_params;
    QSharedPointer<QSsh::SftpChannel>       m_ftp;
    QSsh::SftpJobId                         m_lastJob;

    void                                    doFinish();
    QString                                 passwordCallback(bool &ok);
};


#endif // CSFTPTESTER_H
