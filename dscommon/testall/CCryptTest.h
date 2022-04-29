#ifndef CCRYPTTEST_H
#define CCRYPTTEST_H

#include <QObject>

#include <tomcrypt.h>
#include <tommath.h>

class CTestWindow;

class CCryptTest : public QObject
{
    Q_OBJECT

  public:
    explicit      CCryptTest(QObject* parent = 0);
    ~             CCryptTest();

  public slots:
    void          init();

  private:
    CTestWindow*  m_main;
    rsa_key       m_keyPrivate;
    rsa_key       m_keyPublic;
    bool          m_haveKeyPrivate;
    bool          m_haveKeyPublic;

    void          addCiphers();
    void          generateRsaKeys(const QString& spriv, const QString& spub);
    void          loadRsaKeys(const QString& spriv, const QString& spub);
    int           encryptRsa(const QByteArray& in, const QByteArray& );

    bool          haveKeyFiles(const QString& fileName, QString& spriv, QString& spub);
    void          runKeyGeneration(const QString& spriv, const QString& spub);
    void          runLoadKeys();

  private slots:
    void          pbGenerateKeyPair();
    void          pbEncrypt();
    void          pbDecrypt();
};

#endif // CCRYPTTEST_H
