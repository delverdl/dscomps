#include <QObject>
#include <QString>

enum EByteConvertOption
{
  bcoSpaced,
  bcoNorlmalHex,
  bcoCondensed,
  bcoPrintable
};

inline QString byteArrayToHex(const QByteArray& data, EByteConvertOption bco = bcoCondensed)
{
  QString sResponse;
  QString sFormat = "%1 ";

  if (bco != bcoPrintable)
  { if (bco == bcoNorlmalHex) sFormat.prepend("0x");
    else if (bco == bcoCondensed) sFormat.chop(1);
    for (const char c : data)
      sResponse += QString(sFormat).arg(static_cast<int>(c) & 0xff, 2, 16, QChar('0'));
    if (bco != bcoCondensed) sResponse.chop(1);
  }
  else
   for (const char c : data)
    if (QChar(c).isPrint()) sResponse += c;
    else sResponse += QString("<%1>").arg(static_cast<int>(c) & 0xff, 2, 16, QChar('0'));
  return sResponse;
}

template <typename T>
void release(T*& inst)
{
  if (!inst) return;
  delete inst;
  inst = 0;
}

void releaseLater(QObject*& o)
{ if (!o) return;
  o->deleteLater();
  o = nullptr;
}
