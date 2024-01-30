#ifndef CPOSITEM_HPP
#define CPOSITEM_HPP

#include <QBitArray>
#include <QFile>
#include <QHash>
#include <QImage>
#include <QIODevice>
#include <QList>
#include <QMap>
#include <QPair>
#include <QString>
#include <QTextCodec>

#include <math.h>

class CPosItem
{
    friend class      CPosPrinter;

  public:

    typedef           QList<CPosItem*>    List;
    typedef           QList<QByteArray>   Packets;

    enum              Type
    {
                      tUnknown, tText, tImage, tBarcode, tLineFeed
    };

    CPosItem(const QByteArray& baData = QByteArray()): m_data(baData), m_type(tUnknown)
    {  }
    ~CPosItem()
    { }

    Packets           toPrinter() { return {m_data}; }
    Type              type() { return m_type; }

    static void       deviceWrite(QIODevice* d, const QByteArray& ba, bool wait = true)
    { d->write(ba);
      if (wait) //Wait 3 times it takes to transfer data @9600 baud (that is 1200 B/s)
        d->waitForBytesWritten(static_cast<int>(ceil((ba.size() + 1) * 3000.0 / 1200.0)));
    }

  protected:
    QByteArray        m_data;
    Type              m_type;

    static QByteArray posCommand(const QByteArray& baCommand,
                                 const QByteArray& baData = QByteArray())
    { QByteArray baResult(baCommand);

      if (!baData.isEmpty())
      { baResult.resize(baResult.size() + baData.size());
        memcpy(&baResult.data()[baCommand.size()], baData.constData(),
            static_cast<size_t>(baData.size()));
      }
      return baResult;
    }

    static QByteArray posInit()
    { return QByteArray(std::begin<char>({0x1b, 0x40}), 2); }

    static QByteArray posLineSpacing(quint8 nSpacing)
    { return posCommand(QByteArray(std::begin<char>({0x1b, 0x33}), 2),
                        QByteArray(1, static_cast<char>(nSpacing))); }

    static QByteArray posLineFeed(quint8 nLines = 1)
    { QByteArray result(std::begin<char>({0x1b, 0x64}), 2);

      result += static_cast<char>(nLines);
      return result;
    }

    static QByteArray posCutPaper(bool bFull = true)
    { QByteArray result(std::begin<char>({0x1d, 0x56, 0x00}), 3);

      if (!bFull) result[2] = '\x01';
      return result;
    }

};

class CPosItemText:   public CPosItem
{
  public:
    CPosItemText(const QByteArray& baText, bool b = false, bool u = false,
                 const Qt::Alignment& a = Qt::Alignment())
      : CPosItem(baText), m_alignment(a), m_bold(b), m_underline(u), m_encoding("IBM437")
    { m_type = tText; }

    Packets           toPrinter()
    {
      QByteArray  fmt(3, 0x00), txt = CPosItem::toPrinter().first();

      if (txt.isEmpty()) return Packets();

      Packets     result;
      bool        ac = m_alignment.testFlag(Qt::AlignCenter),
                  ar = m_alignment.testFlag(Qt::AlignRight),
                  ai = ac || ar;

      fmt[0] = '\x1b';
      if (ai && !txt.endsWith('\n')) txt += '\n';
      result << fromUnicode(txt, m_encoding);
      if (ai)
      { fmt[1] = 'a';
        if (ac) fmt[2] = '\x01';
        else if (ar) fmt[2] = '\x02';
        result.prepend(fmt);            //Activate
        fmt[2] = '\x00'; result << fmt; //Deactivate
      }
      if (m_bold)
      { fmt[1] = 'E'; fmt[2] = '\x01';
        result.prepend(fmt);
        fmt[2] = '\x00'; result << fmt;
      }
      if (m_underline)
      { fmt[1] = '-'; fmt[2] = '\x01';
        result.prepend(fmt);
        fmt[2] = '\x00'; result << fmt;
      }
      return result;
    }

    void              setText(const QByteArray& baText) { m_data = baText; }
    void              setAlignment(const Qt::Alignment& aValue) { m_alignment = aValue; }
    void              setBold(bool bValue) { m_bold = bValue; }
    void              setUnderline(bool bValue) { m_underline = bValue; }
    void              setEncoding(const QByteArray& baEnc) { m_encoding = baEnc; }

  private:
    Qt::Alignment     m_alignment;
    bool              m_bold;
    bool              m_underline;
    QByteArray        m_encoding;

    QByteArray        fromUnicode(QString text, const QByteArray& baName)
    {
      QByteArray  ba;
      QTextCodec* tc = QTextCodec::codecForName(baName);

      ba = tc->fromUnicode(text);
      return ba;
    }
};

class CPosItemImage:  public CPosItem
{
  public:
    CPosItemImage(const QByteArray& filename)
      : CPosItem(filename)
    { m_type = tImage; }

    Packets           toPrinter()
    {
      QString     sImageFile = CPosItem::toPrinter().first();
      Packets     result;
      QImage      image;
      QBitArray   imageBits = getImageBits(sImageFile, image);

      if (!imageBits.isEmpty())
      {
        int               x, y, i, k, b, offset = 0;
        bool              v;
        char              slice;

        if (!image.isNull())
        { result << posInit(); //Initialize printer
          result << posLineSpacing(24);
          offset = 0;
          while (offset < image.height())
          { int imageDataLineIndex = 0;
            QByteArray imageDataLine(3 * image.width(), 0);

            for (x = 0; x < image.width(); ++x)
            { for (k = 0; k < 3; ++k)
              { slice = 0;
                for (b = 0; b < 8; ++b)
                { y = (((offset / 8) + k) * 8) + b;
                  i = (y * image.width()) + x;
                  v = false;
                  if (i < imageBits.size()) v = imageBits[i];
                  slice |= static_cast<char>(((v ? 1 : 0) << (7 - b)));
                }
                imageDataLine[imageDataLineIndex + k] = slice;
              }
              imageDataLineIndex += 3;
            }
            result << posImageModeCommand(image.width());
            result << imageDataLine;
            offset += 24;
            result << posLineFeed();
          }
          result << posLineSpacing(30);
        }
      }
      return result;
    }

  private:
    const int         cnThreshold                 = 127;
    const char        cszPosSelectBitImageMode[2] = {0x1b, 0x2a};

    QByteArray        posImageModeCommand(int width) const
    { return posCommand(QByteArray(cszPosSelectBitImageMode, 2),
                        QByteArray(std::begin<char>({33,
                                                    static_cast<char>(width & 0xFF),
                                                    static_cast<char>((width >> 8) & 0xFF)}),
                                   3));
    }

    QBitArray         getImageBits(const QString& sImageFile, QImage& imgData) const
    { int       luminance, offset = 0;
      QBitArray btaImageBits;
      QFile     f(sImageFile);

      if (!f.open(QIODevice::ReadOnly) ||
          !imgData.loadFromData(f.readAll()) ||
          imgData.isNull()      || //Must be valid
          imgData.depth() > 1   || //Must be monochromatic
          imgData.width() > 360 || //Maximum width
          imgData.height() > 160   //Maximum heigh (4/9 aspect ratio)
          ) return btaImageBits;
      btaImageBits.resize(imgData.width() * imgData.height());
      for (int i = 0; i < imgData.height(); i++)
      { for (int j = 0; j < imgData.width(); j++)
        { luminance = static_cast<int>(((imgData.pixel(j, i) & 0x00ff0000) >> 16)  * 0.3   + //red
                            ((imgData.pixel(j, i) & 0x0000ff00) >> 8)   * 0.59  + //green
                            (imgData.pixel(j, i)  & 0x000000ff)         * 0.11);  //blue
          btaImageBits[offset] = luminance < cnThreshold;
          offset++;
        }
      }
      return btaImageBits; //File's closed after returning
    }

};

class CPosItemBarcode:public CPosItem
{
  public:

    enum BarcodeType
    { bctUpcA     = 0x41,
      bctUpcE,
      bctJan13,
      bctJan8,
      bctCode39,
      bctItf,
      bctCodaBar,
      bctCode93,
      bctCode128,
    };

    CPosItemBarcode(const QByteArray& code, BarcodeType bct = bctJan13, quint8 uh = 0xa2)
      : CPosItem(code), m_mode(bct), m_height(uh)
    { m_type = tBarcode; }

    Packets           toPrinter()
    {
      QByteArray baCode = CPosItem::toPrinter().first();

      if (baCode.size() > 255 || !validBarcode(m_mode, baCode)) return Packets();

      baCode.prepend(static_cast<char>(baCode.size() & 0xff));
      baCode.prepend(static_cast<char>(m_mode));
      baCode.prepend(QByteArray(cszPosBarcodePrint, 2));

      Packets result;

      result << posCommand(QByteArray(cszPosBarcodeHeight, 2),
                           QByteArray(1, static_cast<char>(m_height)))
             << baCode;

      return result;
    }

    void              setCode(const QByteArray& baCode) { m_data = baCode; }
    void              setMode(BarcodeType bctValue) { m_mode = bctValue; }
    void              setHeight(quint8 uValue) { m_height = uValue; }

  private:
    BarcodeType       m_mode;
    quint8            m_height;

    typedef           QPair <signed char, signed char>  CMinMax;
    typedef           QList<CMinMax>                    CMinMaxList;
    typedef           QHash<BarcodeType, CMinMaxList>   CMinMaxDict;

    const CMinMaxDict mmdBarcodes {
      {bctUpcA,       {{48, 57}}}, {bctUpcE,    {{48, 57}}}, {bctJan13,   {{48, 57}}},
      {bctJan8,       {{48, 57}}}, {bctItf,     {{48, 57}}}, {bctCode93,  {{1, 127}}},
      {bctCode128,    {{1, 127}}},
      {bctCode39,     {{48, 57}, {65, 90}, {32, -1}, {32, -1}, {36, -1}, {37, -1},
                       {43, -1}, {45, -1}, {46, -1}, {47, -1}}},
      {bctCodaBar,    {{48, 57}, {65, 68}, {36, -1}, {43, -1}, {45, -1}, {46, -1}, {47, -1},
                       {58, -1}}}
    };

    const char        cszPosBarcodePrint[2]       = {0x1d, 0x6b};
    //const char        cszPosBarcodeFont[2]        = {0x1d, 0x66};
    const char        cszPosBarcodeHeight[2]      = {0x1d, 0x68};

    bool              validBarcode(BarcodeType bctValue, const QByteArray& baCode)
    { bool b = false;

      switch (bctValue)
      { case bctUpcA    :
        case bctUpcE    : b = baCode.size() == 12; break;
        case bctJan13   : b = baCode.size() == 13; break;
        case bctJan8    : b = baCode.size() == 8; break;
        case bctCode39  :
        case bctItf     :
        case bctCodaBar :
        case bctCode93  :
        case bctCode128 :
        { bool b = baCode.size() > 0 && baCode.size() <= 255;

          if (bctValue == bctItf) b &= (baCode.size() % 2 == 0);
          else if (bctValue == bctCode128) b &= (baCode.size() > 1);
          break;
        }
      }
      if (b) //Valid code size
      { auto mml = mmdBarcodes.value(bctValue);

        for (const char c : baCode)
        { bool fnd = false;

          for (const CMinMax& mm : mml)
          { char mn = mm.first, mx = mm.second;

            if ((mx > 0 && c >= mn && c <= mx) || c == mn) { fnd = true; break; }
          }
          if (!fnd) { b = false; break; }
        }
      }
      return b;
    }

};

class CPosItemLineFeed: public CPosItem
{
  public:
    CPosItemLineFeed(int nLines = 1): CPosItem(), m_lines(nLines) { m_type = tLineFeed; }

    Packets           toPrinter()
    { return {posLineFeed(static_cast<quint8>(m_lines))}; }

    void              setLines(int nLines) { m_lines = nLines; }

  private:
    int               m_lines;
};

/*** EXAMPLE ****
 *
    CPosItem::List toPrint;

    toPrint << new CPosItemLineFeed
            << new CPosItemImage("D:/projects/pq-all-center-02.png")
            << new CPosItemLineFeed
            << new CPosItemText("Prueba de impresión de texto", true, false, Qt::AlignCenter)
            << new CPosItemLineFeed
            << new CPosItemText("Mes\tCol1\tCol2\tCol3")
            << new CPosItemLineFeed
            << new CPosItemText("Enero\t5002\t403\t380")
            << new CPosItemLineFeed
            << new CPosItemText("Febrero\t667\t704\t99212")
            << new CPosItemLineFeed
            << new CPosItemText("Marzo\t12292\t122\t7534")
            << new CPosItemLineFeed(3)
            << new CPosItemBarcode("1234567890123")
            << new CPosItemLineFeed(8)
               ;

    QSerialPort* printer = new QSerialPort;

    printer->setPortName("COM1");
    printer->setBaudRate(9600);
    printer->setDataBits(QSerialPort::Data8);
    printer->setParity(QSerialPort::NoParity);
    printer->setStopBits(QSerialPort::OneStop);
    printer->setFlowControl(QSerialPort::NoFlowControl);
    if (printer->open(QIODevice::WriteOnly))
    {
      printer->clear();
      for (CPosItem* pi : toPrint)
      {
        auto pkts = pi->toPrinter();

        for (const QByteArray& ba : pkts)
          CPosItem::deviceWrite(printer, ba);
      }
    }
    else
      printf("Error opening port: %d", (int) printer->error());
 *
 */


#endif // CPOSITEM_HPP
