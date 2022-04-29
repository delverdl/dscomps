#include "CCryptTest.h"
#include "CTestWindow.h"
#include "TestExceptions.hpp"
#include "ui_CTestWindow.h"

#include <QBuffer>
#include <QFile>
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>

CCryptTest::CCryptTest(QObject* parent)
  : QObject(parent), m_main(qobject_cast<CTestWindow*>(parent)),
    m_haveKeyPrivate(false)
{  }

CCryptTest::~CCryptTest()
{  }

void CCryptTest::init()
{
  Ui::CTestWindow* w = m_main->ui;

  addCiphers();

  connect(w->pbCryptKeysPair,   SIGNAL(clicked(bool)), SLOT(pbGenerateKeyPair()));
  connect(w->pbCryptEncrypt,    SIGNAL(clicked(bool)), SLOT(pbEncrypt()));
  connect(w->pbCryptDecrypt,    SIGNAL(clicked(bool)), SLOT(pbDecrypt()));
  connect(w->pbCryptUseCipher,  SIGNAL(clicked(bool)),
          w->cbxCryptCipher,    SLOT(setEnabled(bool)));
}

void CCryptTest::addCiphers()
{
  Ui::CTestWindow* w = m_main->ui;

#ifdef LTC_RIJNDAEL
  register_cipher (&aes_desc);
  w->cbxCryptCipher->addItem(QPixmap(":/cipher.png"), aes_desc.name,
                             qVariantFromValue<void*>((void*) &aes_desc));
#endif
#ifdef LTC_BLOWFISH
  register_cipher (&blowfish_desc);
  w->cbxCryptCipher->addItem(QPixmap(":/cipher.png"), blowfish_desc.name,
                             qVariantFromValue<void*>((void*) &blowfish_desc));
#endif
#ifdef LTC_XTEA
  register_cipher (&xtea_desc);
//
  w->cbxCryptCipher->addItem(QPixmap(":/cipher.png"), xtea_desc.name,
                             qVariantFromValue<void*>((void*) &xtea_desc));
#endif
#ifdef LTC_RC5
  register_cipher (&rc5_desc);
  w->cbxCryptCipher->addItem(QPixmap(":/cipher.png"), rc5_desc.name,
                             qVariantFromValue<void*>((void*) &rc5_desc));
#endif
#ifdef LTC_RC6
  register_cipher (&rc6_desc);
  w->cbxCryptCipher->addItem(QPixmap(":/cipher.png"), rc6_desc.name,
                             qVariantFromValue<void*>((void*) &rc6_desc));
#endif
#ifdef LTC_SAFERP
  register_cipher (&saferp_desc);
  w->cbxCryptCipher->addItem(QPixmap(":/cipher.png"), saferp_desc.name,
                             qVariantFromValue<void*>((void*) &saferp_desc));
#endif
#ifdef LTC_TWOFISH
  register_cipher (&twofish_desc);
  w->cbxCryptCipher->addItem(QPixmap(":/cipher.png"), twofish_desc.name,
                             qVariantFromValue<void*>((void*) &twofish_desc));
#endif
#ifdef LTC_SAFER
  register_cipher (&safer_k64_desc);
  register_cipher (&safer_sk64_desc);
  register_cipher (&safer_k128_desc);
  register_cipher (&safer_sk128_desc);
  w->cbxCryptCipher->addItem(QPixmap(":/cipher.png"), safer_k64_desc.name,
                                      qVariantFromValue<void*>((void*) &safer_k64_desc));
  w->cbxCryptCipher->addItem(QPixmap(":/cipher.png"), safer_sk64_desc.name,
                                      qVariantFromValue<void*>((void*) &safer_sk64_desc));
  w->cbxCryptCipher->addItem(QPixmap(":/cipher.png"), safer_k128_desc.name,
                                      qVariantFromValue<void*>((void*) &safer_k128_desc));
  w->cbxCryptCipher->addItem(QPixmap(":/cipher.png"), safer_sk128_desc.name,
                                      qVariantFromValue<void*>((void*) &safer_sk128_desc));
#endif
#ifdef LTC_RC2
  register_cipher (&rc2_desc);
  w->cbxCryptCipher->addItem(QPixmap(":/cipher.png"), rc2_desc.name,
                             qVariantFromValue<void*>((void*) &rc2_desc));
#endif
#ifdef LTC_DES
  register_cipher (&des_desc);
  register_cipher (&des3_desc);
  w->cbxCryptCipher->addItem(QPixmap(":/cipher.png"), des_desc.name,
                             qVariantFromValue<void*>((void*) &des_desc));
  w->cbxCryptCipher->addItem(QPixmap(":/cipher.png"), des3_desc.name,
                             qVariantFromValue<void*>((void*) &des3_desc));
#endif
#ifdef LTC_CAST5
  register_cipher (&cast5_desc);
  w->cbxCryptCipher->addItem(QPixmap(":/cipher.png"), cast5_desc.name,
                             qVariantFromValue<void*>((void*) &cast5_desc));
#endif
#ifdef LTC_NOEKEON
  register_cipher (&noekeon_desc);
  w->cbxCryptCipher->addItem(QPixmap(":/cipher.png"), noekeon_desc.name,
                             qVariantFromValue<void*>((void*) &noekeon_desc));
#endif
#ifdef LTC_SKIPJACK
  register_cipher (&skipjack_desc);
  w->cbxCryptCipher->addItem(QPixmap(":/cipher.png"), skipjack_desc.name,
                             qVariantFromValue<void*>((void*) &skipjack_desc));
#endif
#ifdef LTC_KHAZAD
  register_cipher (&khazad_desc);
  w->cbxCryptCipher->addItem(QPixmap(":/cipher.png"), khazad_desc.name,
                             qVariantFromValue<void*>((void*) &khazad_desc));
#endif
#ifdef LTC_ANUBIS
  register_cipher (&anubis_desc);
  w->cbxCryptCipher->addItem(QPixmap(":/cipher.png"), anubis_desc.name,
                             qVariantFromValue<void*>((void*) &anubis_desc));
#endif

  if (register_hash(&whirlpool_desc) == -1)
  { printf("Error registering Whirlpool hash\n"); exit(-1); }
  if (register_prng(&sprng_desc) == -1)
  { printf("Error registering system random generator\n"); exit(-1); }

  /*Register math library*/
  ltc_mp = ltm_desc;
}

void CCryptTest::generateRsaKeys(const QString& spriv, const QString& spub)
{
  #define errf_(n)  do { result = n; goto _gkf_err; } while (0)
  #define errk_     if (result != CRYPT_OK) goto _gkk_err

  int     prng_idx = find_prng("sprng"), result;
  uchar   buffer[2048];
  QFile   fkey(spub);
  ulong   x = 2048;

  result = rsa_make_key(nullptr, prng_idx, 1024/8, 65537, &m_keyPrivate);
  if (result != CRYPT_OK)
_gkk_err:
    throw CKeyExportException(result);
  if (!fkey.open(QIODevice::WriteOnly))
  {
    result = EACCES;
_gkf_err:
    fkey.close();
    QFile::remove(spub); QFile::remove(spriv);
    throw CFileOutputException(result);
  }
  result = rsa_export(buffer, &x, PK_PUBLIC, &m_keyPrivate); errk_;
  result = rsa_import(buffer, x, &m_keyPublic); errk_; //Import for internal access
  if (fkey.write(reinterpret_cast<const char*>(buffer), x) != static_cast<qint64>(x)) errf_(ENOSPC);

  fkey.close();
  fkey.setFileName(spriv);
  if (!fkey.open(QIODevice::WriteOnly)) errf_(EACCES);
  x = 2048;
  result = rsa_export(buffer, &x, PK_PRIVATE, &m_keyPrivate); errk_;
  if (fkey.write(reinterpret_cast<const char*>(buffer), x) != static_cast<qint64>(x)) errf_(ENOSPC);
  fkey.close();

  #undef errf_
  #undef errk_
}

void loadOneKey(const QString& sname, bool& bHaveKey, rsa_key* rsaKey, int nType)
{
  #define     errf_(n)  do { result = n; goto _lkf_err; } while (0)

  QFile       fkey;
  QByteArray  ba;
  int         result;

  if (!QFile::exists(sname)) return;
  fkey.setFileName(sname);
  if (!fkey.open(QIODevice::ReadOnly))
  {
    result = EACCES; //May be another type of error but this' much alike.
_lkf_err:
    fkey.close();
    throw CFileInputException(result);
  }
  ba = fkey.readAll(); if (!ba.size()) errf_(ENODATA);
  result = rsa_import(reinterpret_cast<const uchar*>(ba.constData()),
                      static_cast<ulong>(ba.size()), rsaKey);
  if (result != CRYPT_OK)
_lkk_err:
    throw CKeyImportException(result);
  if (rsaKey->type != nType) { result = CRYPT_PK_TYPE_MISMATCH; goto _lkk_err; }
  bHaveKey = true;
  fkey.close();

  #undef errf_
}

void CCryptTest::loadRsaKeys(const QString& spriv, const QString& spub)
{
  loadOneKey(spriv, m_haveKeyPrivate, &m_keyPrivate,  PK_PRIVATE);
  loadOneKey(spub, m_haveKeyPublic,  &m_keyPublic,   PK_PUBLIC);
}

static const char* cszKeyPriv = "priv";
static const char* cszKeyPub = "pub";
static const char* cszKeyName = "%1_%2.pem";
static const char* cszKeyPath = "%1/ued";

bool CCryptTest::haveKeyFiles(const QString& fileName, QString& spriv, QString& spub)
{
  spriv = QString(cszKeyName).arg(fileName, cszKeyPriv);
  spub = QString(cszKeyName).arg(fileName, cszKeyPub);

  return QFile::exists(spriv) || QFile::exists(spub);
}

void CCryptTest::runKeyGeneration(const QString& spriv, const QString& spub)
{
  m_haveKeyPrivate = m_haveKeyPublic = false;
  generateRsaKeys(spriv, spub);
}

void CCryptTest::runLoadKeys()
{
  QString spriv, spub;

  //This check may change depending on application's purpose
  if (!m_haveKeyPrivate | !m_haveKeyPublic)
  {
    if (haveKeyFiles(QString(cszKeyPath).arg(QDir::homePath()), spriv, spub))
      loadRsaKeys(spriv, spub);
    if (!m_haveKeyPrivate ) runKeyGeneration(spriv, spub);
  }
}

void CCryptTest::pbGenerateKeyPair()
{
  QString s = QFileDialog::getSaveFileName(m_main, "Keys base name", QDir::homePath()),
          spriv, spub;

  if (s.isEmpty())
    return;
  if (haveKeyFiles(s, spriv, spub))
  {
    int     r = QMessageBox::warning(m_main, "Warning",
                                     "Key files exist, do you want to proceed?",
                                     QMessageBox::Yes | QMessageBox::No);

    if (r == (int) QMessageBox::No) return;
  }
  try
  {
    runKeyGeneration(spriv, spub);
    QMessageBox::information(m_main, "Info", "Key files has been correctly generated!");
  }
  catch (CKeyExportException& e)
  { QMessageBox::critical(m_main, "Error", QString(e.what())); }
  catch (CFileOutputException& e)
  { QMessageBox::critical(m_main, "Error", QString(e.what())); }
}

void CCryptTest::pbEncrypt()
{
  Ui::CTestWindow*  w = m_main->ui;

  QMessageBox::warning(m_main, "Warning",
                       "Method not completed. In order to test this you must "\
                       "edit the source code and do it your own way... sorry!");

  return;

  try
  {
    if (!w->pbCryptUseCipher->isChecked())
    {
      runLoadKeys();
    }
    else
    {
      //
    }
  }
  catch (std::exception& e)
  { QMessageBox::critical(m_main, "Error", QString(e.what())); }
}

void CCryptTest::pbDecrypt()
{
  Ui::CTestWindow* w = m_main->ui;

  QMessageBox::warning(m_main, "Warning",
                       "Method not completed. In order to test this you must "\
                       "edit the source code and do it your own way... sorry!");

  return;

  int         nResult;
  QByteArray  baInput = QByteArray::fromBase64(w->leCryptEncrypted->text().toLatin1());
  QByteArray  baOutput;
  QBuffer     iBuffer(&baInput), oBuffer(&baOutput);
  char        iBlock[MAXBLOCKSIZE], oBlock[MAXBLOCKSIZE];
  qint64      nRead, nWritten;

  //Open buffers
  iBuffer.open(QIODevice::ReadOnly); //Input was taken from a base-64 encoded string
  oBuffer.open(QIODevice::WriteOnly);
  try
  {
    if (!w->pbCryptUseCipher->isChecked())
    {
      int         nPrng = find_prng("sprng"), nStat;

      runLoadKeys();
      while (!iBuffer.atEnd())
      {
        //Read block
        nRead = iBuffer.read(iBlock, 64);
        if (nRead > 0)
        {
          //Decrypt block using public key
          nWritten = MAXBLOCKSIZE;
          nResult = rsa_decrypt_key(reinterpret_cast<const uchar*>(iBlock),
                                    static_cast<ulong>(nRead),
                                    reinterpret_cast<uchar*>(oBlock),
                                    reinterpret_cast<ulong*>(&nWritten),
                                    nullptr, 0, nPrng,
                                    &nStat, &m_keyPrivate);
          if (nResult != CRYPT_OK)
            throw CKeyDecryptException(nResult);
          oBuffer.write(oBlock, nWritten); //Write decrypted block
        }
      }
      //Set data to output line edit
      w->leCryptDecrypted->setText(baOutput);
    }
    else
    { //Decrypt using selected cipher
      int           nCipherIndex, nHashIndex, nHashSize, nBlockLength;
      QString       sCipher = w->cbxCryptCipher->currentText();
      QString       sKey;
      bool          ok = false;
      uchar         ucKEY[MAXBLOCKSIZE], ucIV[MAXBLOCKSIZE];
      symmetric_CTR scCipher;

      if (sCipher.isEmpty()) throw CCipherDecryptException(CRYPT_INVALID_ARG);
      nCipherIndex = find_cipher(sCipher.toLocal8Bit().constData());
      if (nCipherIndex == -1) throw CCipherDecryptException(CRYPT_INVALID_CIPHER);
      nHashIndex = find_hash("whirlpool");
      if (nHashIndex == -1) throw CCipherDecryptException(CRYPT_INVALID_HASH);
      nBlockLength = cipher_descriptor[nCipherIndex].block_length;
      nHashSize = static_cast<int>(hash_descriptor[nHashIndex].hashsize);
      nResult = cipher_descriptor[nCipherIndex].keysize(&nHashSize);
      if (nResult != CRYPT_OK) throw CCipherDecryptException(nResult);
      do
      {
        sKey  = QInputDialog::getText(m_main, "Chiper Encryption", "Enter password",
                                      QLineEdit::Password, QString(), &ok);
        qt_noop();
      } while ((sKey.isEmpty() && ok) || //Key must not be empty
               !sKey.isEmpty());         //Key is not empty
      if (ok)
      {
        nWritten = MAXBLOCKSIZE;
        //Make whirlpool hash of password
        nResult = hash_memory(nHashIndex, reinterpret_cast<const uchar*>(sKey.toLatin1().data()),
                              static_cast<ulong>(sKey.length()), ucKEY,
                              reinterpret_cast<ulong*>(&nWritten));
        if (nResult != CRYPT_OK)
_cde:     throw CCipherDecryptException(nResult);
        //Read IV block
        if (!iBuffer.atEnd())
        {
          nRead = iBuffer.read(reinterpret_cast<char*>(ucIV), nBlockLength);
          if (nRead != nBlockLength)
_bie:       throw CBufferInputException(ENODATA);
          nResult = ctr_start(nCipherIndex, ucIV, ucKEY, nHashSize, 0,
                              CTR_COUNTER_LITTLE_ENDIAN, &scCipher);
          if (nResult != CRYPT_OK) goto _cde;
        }
        else goto _bie;
        //Read rest of input buffer
        if (!iBuffer.atEnd())
        {
          nRead = iBuffer.read(iBlock, 64);
          if (nRead < 0) goto _bie;
          oBuffer.write(iBlock);
        }
        nResult = 0 /*ctr_decrypt()*/;
      }
    }
  }
  catch (std::exception& e)
  { QMessageBox::critical(m_main, "Error", QString(e.what())); }
}
