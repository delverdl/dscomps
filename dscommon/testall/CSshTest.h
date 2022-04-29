#ifndef CSSHTEST_H
#define CSSHTEST_H

#include <QObject>

class CTestWindow;

#include <sshconnection.h>
#include <sshconnectionmanager.h>

class CSshTest : public QObject
{
    Q_OBJECT

  public:
    explicit                                CSshTest(QObject* parent = nullptr);
    ~                                       CSshTest();

    bool                                    isConnected();

  public slots:
    void                                    init();

  private:
    CTestWindow*                            m_main;

    QSsh::SshConnection*                    m_cnx;
    QSsh::SshConnectionParameters           m_params;
    QSharedPointer<QSsh::SshRemoteProcess>  m_process;

    void                                    doFinish();

  private slots:
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

    //UI
    void                                    buttonWantDialog();
    void                                    buttonConnect();
    void                                    editModified(const QString& s);
    void                                    editReturnPressed();
};

#endif // CSSHTEST_H
