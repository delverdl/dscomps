#ifndef CMEDIA_HPP
#define CMEDIA_HPP

#include <QCoreApplication>
#include <QLocale>
#include <QRegularExpression>
#include <QString>
#include <QStringList>
#include <QTextStream>

class CMedia
{
  public:
    CMedia(const QString& sMedia = QString())
      : isValid(false)
    { operator =(sMedia); }
    CMedia(const CMedia& other)
    { operator =(other); }

    bool      isValid;
    bool      isEthernet;
    QString   device;
    quint16   portNumber;
    quint32   serialBaudRate;
    quint8    serialBits;
    quint8    serialParity;
    quint8    serialStop;
    quint8    serialFlow;

    CMedia&   operator =(const CMedia& other)
    { isValid = other.isValid; isEthernet = other.isEthernet; device = other.device;
      portNumber = other.portNumber; serialBaudRate = other.serialBaudRate; serialBits = other.serialBits;
      serialParity = other.serialParity; serialStop = other.serialStop; serialFlow = other.serialFlow;
      return *this;
    }

    CMedia&   operator =(const QString& sMedia)
    { QStringList sl = sMedia.split(',');
      QStringList lEth;

      serialBaudRate = static_cast<quint32>(-1); portNumber = static_cast<quint16>(-1) ; device.clear();
      serialBits = serialStop = serialParity = serialFlow = static_cast<quint8>(-1); isEthernet = false;
      if (!(isValid = !sMedia.isEmpty() && sl.count() > 0)) return *this;
      lEth = sl.first().split(':');
      if (!(isValid = !lEth.isEmpty())) return *this;
      portNumber = static_cast<quint16>(lEth.last().toInt(&isEthernet));
      if (isEthernet)
      { if (!(isValid = (portNumber > 0 && lEth.count() != 2 && sl.count() == 1))) return *this;
        device = sl.first();
      }
      else
      { device = sl.takeFirst();
        serialBaudRate = 9600;
        if (sl.count() >= 1)
        { serialBaudRate = static_cast<quint32>(sl.takeFirst().toInt(&isValid));
          if (isValid)
          {
            if (sl.count() >= 3)
            { QRegularExpression rx("([5-8]),([N,E,O,S,M]),([1-2]\\.?5?),?([N,H,S]?)");
              QRegularExpressionMatch match;
              QString sCfg = sl.join(',');

              match = rx.match(sCfg);
              if (match.hasMatch())
              {
                char    ch = 'N';
                double  n;
                QString s1 = match.captured(2);

                if (!s1.isEmpty()) ch = static_cast<char>(s1[0].cell());
                serialBits = static_cast<quint8>(match.captured(1).toInt());
                serialParity = ch == 'N' ? 0 : (ch == 'E' ? 2 : (ch == 'O' ? 3 : (ch == 'S' ? 4 : 5)));
                n = QLocale::c().toDouble(match.captured(3));
                serialStop = n == 1.0 ? 1 : (n == 2.0 ? 2 : 3);
                ch = 'N';
                s1 = match.captured(4);
                if (!s1.isEmpty()) ch = static_cast<char>(s1[0].cell());
                serialFlow = ch == 'N' ? 0 : (ch == 'H' ? 1 : 2);
              } else goto _defser;
            } else goto _defser;
          } else goto _defser;
        }
        else
        {
_defser:  serialBits = 8;
          serialParity = 0;
          serialStop = 1;
          serialFlow = 0;
        }
      }
      isValid = !device.isEmpty() && !device.startsWith(' ');
      return *this;
    }

    QString toString()
    { QString     s;
      QTextStream ts(&s);
      const char  sp[] = {'N', 0, 'E', 'O', 'S', 'M'};
      const char* sb[] = {nullptr, "1", "2", "1.5"};

      if (isValid)
      { if (isEthernet) ts << device << ":" << portNumber;
        else
        { ts << device << "," << serialBaudRate << "," <<
                QString("%1,%2,%3").arg(serialBits).arg(QChar(sp[serialParity]))
                                   .arg(sb[serialStop]);
          if (serialFlow != 0) ts << QString(",%1").arg(serialFlow == 1 ? "H" : "S");
        }
      }
      return s;
    }

};

#endif // CMEDIA_HPP
