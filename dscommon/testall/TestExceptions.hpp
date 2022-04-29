#ifndef TESTEXCEPTIONS_HPP
#define TESTEXCEPTIONS_HPP

#include <QString>
#include <tomcrypt.h>

class CLocalException: public std::exception
{
  public:
    CLocalException(): std::exception() {}
    virtual ~CLocalException() {}

    const char* what() const noexcept;

  protected:
    QString     m_s;
};

const char*CLocalException::what() const noexcept
{ return m_s.toLatin1().constData(); }

class CStandardException: public CLocalException
{
  public:
    CStandardException(int r, const char* sact, const char* styp) : CLocalException()
    {
      m_s = QString("%1 %2 error %3: %4")
            .arg(QString(styp))
            .arg(QString(sact))
            .arg(r)
            .arg(QString(strerror(r)));
    }
    ~CStandardException();
};

CStandardException::~CStandardException() {}

class CStandardInputException: public CStandardException
{
  public:
    CStandardInputException(int r, const char* styp):
      CStandardException(r, "input", styp) {}
    ~CStandardInputException();
};

CStandardInputException::~CStandardInputException() {}

class CStandardOutputException: public CStandardException
{
  public:
    CStandardOutputException(int r, const char* styp):
      CStandardException(r, "output", styp) {}
    ~CStandardOutputException();
};

CStandardOutputException::~CStandardOutputException() {}

class CFileInputException: public CStandardInputException
{
  public:
    CFileInputException(int r): CStandardInputException(r, "File") {}
    ~CFileInputException();
};

CFileInputException::~CFileInputException() {}

class CFileOutputException: public CStandardOutputException
{
  public:
    CFileOutputException(int r): CStandardOutputException(r, "File") {}
    ~CFileOutputException();
};

CFileOutputException::~CFileOutputException() {}

class CBufferInputException: public CStandardInputException
{
  public:
    CBufferInputException(int r): CStandardInputException(r, "Buffer") {}
    ~CBufferInputException();
};

CBufferInputException::~CBufferInputException() {}

class CBufferOutputException: public CStandardOutputException
{
  public:
    CBufferOutputException(int r): CStandardOutputException(r, "Buffer") {}
    ~CBufferOutputException();
};

CBufferOutputException::~CBufferOutputException() {}

class CKeyException: public CLocalException
{
  public:
    CKeyException(int r, const char* sact) : CLocalException()
    {
      m_s = QString("Key %1 error %2: %3")
            .arg(QString(sact))
            .arg(r)
            .arg(QString(error_to_string(r)));
    }
    ~CKeyException();
};

CKeyException::~CKeyException() {}

class CKeyImportException: public CKeyException
{
  public:
    CKeyImportException(int r) : CKeyException(r, "import") {}
    ~CKeyImportException();
};

CKeyImportException::~CKeyImportException() {}

class CKeyExportException: public CKeyException
{
  public:
    CKeyExportException(int r) : CKeyException(r, "export") {}
    ~CKeyExportException();
};

CKeyExportException::~CKeyExportException() {}

class CKeyEncryptException: public CKeyException
{
  public:
    CKeyEncryptException(int r) : CKeyException(r, "encryption") {}
    ~CKeyEncryptException();
};

CKeyEncryptException::~CKeyEncryptException() {}

class CKeyDecryptException: public CKeyException
{
  public:
    CKeyDecryptException(int r) : CKeyException(r, "decryption") {}
    ~CKeyDecryptException();
};

CKeyDecryptException::~CKeyDecryptException() {}

class CCipherException: public CLocalException
{
  public:
    CCipherException(int r, const char* sact) : CLocalException()
    {
      m_s = QString("%1 by cipher error %2: %3")
            .arg(QString(sact))
            .arg(r)
            .arg(QString(error_to_string(r)));
    }
    ~CCipherException();
};

CCipherException::~CCipherException() {}

class CCipherDecryptException: public CCipherException
{
  public:
    CCipherDecryptException(int r): CCipherException(r, "Decryption") {}
    ~CCipherDecryptException();
};

CCipherDecryptException::~CCipherDecryptException() {}

class CCipherEncryptException: public CCipherException
{
  public:
    CCipherEncryptException(int r): CCipherException(r, "Encryption") {}
    ~CCipherEncryptException();
};

CCipherEncryptException::~CCipherEncryptException() {}

#endif // TESTEXCEPTIONS_HPP
