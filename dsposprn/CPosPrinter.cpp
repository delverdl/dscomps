#include "CPosPrinter.h"

#include <AppUtils.hpp>
#include <CMedia>

#include <QTimer>

Q_LOGGING_CATEGORY(drvPos, "driver.pos")

CPosPrinter::CPosPrinter(QObject *parent) :
  QObject(parent), printer(nullptr), isConnected(false), isExternal(false), isSerial(true)
{  }

CPosPrinter::~CPosPrinter()
{ releaseMemory(); }

void CPosPrinter::openMedia(const QString& sDevice)
{ CMedia m(sDevice);

  printer = nullptr;
  isConnected = false;
  isExternal = false;
  if (!m.isValid)
  { qCCritical(drvPos) << tr("Invalid media to connect to: %1")
                          .arg(sDevice).toUtf8().data();
    emitStatus(dsErrorFatal);
    return;
  }
  isSerial = !m.isEthernet;
  if (isSerial)
  { QSerialPort*  port = new QSerialPort(this);

    printer = port;
    if (port)
    { port->setPortName(m.device);
      port->setBaudRate(static_cast<qint32>(m.serialBaudRate));
      port->setDataBits(static_cast<QSerialPort::DataBits>(m.serialBits));
      port->setParity(static_cast<QSerialPort::Parity>(m.serialParity));
      port->setStopBits(static_cast<QSerialPort::StopBits>(m.serialStop));
      port->setFlowControl(static_cast<QSerialPort::FlowControl>(m.serialFlow));
      if (port->open(QIODevice::ReadWrite))
      { isConnected = true;
        qCInfo(drvPos) << tr("Serial port opened").toUtf8().data();
        QTimer::singleShot(0, this, [this] () { emitStatus(dsNoError); } );
      }
      else QTimer::singleShot(0, this, [this] () { emitStatus(dsErrorOpen); } );
    } else QTimer::singleShot(0, this, [this] () { emitStatus(dsErrorMemory); } );
  }
  else
  { QTcpSocket* socket = new QTcpSocket(this);

    if (socket)
    { printer = socket;
      connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), SLOT(socketError(QAbstractSocket::SocketError)));
      connect(socket, SIGNAL(connected()), SLOT(socketConnected()));
      connect(socket, SIGNAL(disconnected()), SLOT(socketDisconnected()));
      socket->connectToHost(m.device, m.portNumber);
    } else QTimer::singleShot(0, this, [this] () { emitStatus(dsErrorMemory); } );
  }
  connect(printer, SIGNAL(bytesWritten(qint64)), SLOT(bytesWritten(qint64)));
}

void CPosPrinter::openMedia(QIODevice* bus)
{ printer = bus;
  isConnected = printer->isOpen();
  isExternal = true;
  isSerial = false;
  connect(printer, SIGNAL(bytesWritten(qint64)), SLOT(bytesWritten(qint64)));
  if (isConnected)
  { qCInfo(drvPos) << tr("External media bus opened").toUtf8().data();
    emitStatus(dsNoError);
  }
  else
  { disconnect();
    emitStatus(dsErrorNotStarted);
  }
}

void CPosPrinter::closeMedia()
{ qCInfo(drvPos) << tr("Driver closed").toUtf8().data();
  releaseMemory();
}

void CPosPrinter::setStatusReport(CAbstractMedia::CbDeviceStatus ds)
{ deviceStatus = ds; }

void CPosPrinter::printDocument(const CPosItem::List& pdData)
{ if (!isReady()) return;
  toSend.clear();
  for (CPosItem* pi : pdData) toSend << pi->toPrinter();
  qCDebug(drvPos) << tr("Packets o send to printer: %1")
                     .arg(toSend.count()).toUtf8().data();
  if (!toSend.isEmpty())
    QTimer::singleShot(0, this, SLOT(writePacket()));
}

void CPosPrinter::printerFeed(int nLines)
{ if (!isReady()) return;
  toSend << CPosItem::posLineFeed(static_cast<quint8>(nLines));
  qCDebug(drvPos) << tr("To print line feed").toUtf8().data();
  QTimer::singleShot(0, this, SLOT(writePacket()));
}

void CPosPrinter::printerSendRaw(const QByteArray& baRaw)
{ if (!isReady()) return;
  toSend << baRaw;
  qCDebug(drvPos) << tr("Raw data to be sent: %1").arg(byteArrayToHex(baRaw)).toUtf8().data();
  QTimer::singleShot(0, this, SLOT(writePacket()));
}

void CPosPrinter::setPrintDone(CAbstractPrinter::CbPrintDone cbPrint)
{ printDone = cbPrint; }

const DeviceStatus cDErrListNet[] = {
  dsErrorOpen, dsErrorNotStarted, dsErrorNoMedia,  dsErrorOpen, dsErrorMemory,
  dsErrorTimeout, dsErrorRead, dsErrorFatal, dsErrorMemory, dsErrorMemory,
  dsErrorFatal, dsErrorFatal, dsErrorFatal, dsErrorWrite, dsErrorOpen,
  dsErrorNotStarted, dsErrorTimeout, dsErrorNoMedia, dsErrorRead, dsErrorWrite,
  dsErrorMemory, dsErrorWrite, dsErrorTimeout
};

const DeviceStatus cDErrListSerial[] = {
  dsNoError, dsErrorNoMedia, dsErrorFatal, dsErrorOpen, dsErrorMemory,
  dsErrorMemory, dsErrorMemory, dsErrorWrite, dsErrorRead, dsErrorMemory,
  dsErrorFatal, dsErrorFatal, dsErrorTimeout, dsErrorNotStarted
};

void CPosPrinter::checkDeviceError(int nError, bool bTcp)
{ DeviceStatus de = bTcp ? (nError < 0 ? dsErrorFatal : cDErrListNet[nError]) :
                           cDErrListSerial[nError];

  qCCritical(drvPos) << tr("Driver error: %1").arg(nError).toUtf8().data();
  isConnected = false;
  emitStatus(de);
}

void CPosPrinter::emitStatus(DeviceStatus de)
{ if (deviceStatus) deviceStatus(de); }

void CPosPrinter::emitPrintDone(bool b)
{ if (printer && printer->bytesToWrite())
  { //If device's something to write already then wait a little bit
    QTimer::singleShot(10, this, [this] () { emitPrintDone(); });
    return;
  }
  qCInfo(drvPos) << tr("Print done!").toUtf8().data();
  if (printDone) printDone(b);
}

void CPosPrinter::releaseMemory()
{ if (!printer) return;
  if (!isExternal)
  { emitStatus(dsClosed);
    printer->disconnect(); //Disconnect all signals
    if (isSerial)
    { QSerialPort* port = qobject_cast<QSerialPort*>(printer);

      port->close();
      delete port;
    }
    else
    { QTcpSocket* socket = qobject_cast<QTcpSocket*>(printer);

      socket->abort();
      delete socket;
    }
  }
  qCInfo(drvPos) << tr("Driver memory freed").toUtf8().data();
  printer = nullptr;
  qt_noop();
}

bool CPosPrinter::isReady()
{ if (!isConnected || !printer) { emitStatus(dsErrorNotStarted); return false; }
  if (!toSend.isEmpty()) { emitStatus(dsErrorNotIdle); return false; }
  return true;
}

void CPosPrinter::bytesWritten(qint64 bytes)
{ quint64 nTime = static_cast<quint64>(bytes * 1 / 3);

  if (!toSend.isEmpty())
  { toSend.removeFirst(); //Remove first packet after writing it
    //Start sending new packet if it's available, but waiting long enough for previous
    //to be properly sent
    if (!toSend.isEmpty()) QTimer::singleShot(static_cast<int>(nTime), this, SLOT(writePacket()));
    else QTimer::singleShot(static_cast<int>(nTime), this, [this] () { emitPrintDone(); });
  } else QTimer::singleShot(static_cast<int>(nTime), this, [this] () { emitPrintDone(); });
}

void CPosPrinter::socketError(QAbstractSocket::SocketError error)
{ checkDeviceError(static_cast<int>(error), true); }

void CPosPrinter::socketConnected()
{ isConnected = true;
  qCInfo(drvPos) << tr("TCP socket opened").toUtf8().data();
  emitStatus(dsNoError);
}

void CPosPrinter::socketDisconnected()
{ isConnected = false;
  qCInfo(drvPos) << tr("TCP socket closed").toUtf8().data();
  releaseMemory();
}

void CPosPrinter::writePacket()
{ if (!toSend.isEmpty() && printer) //Write a single packet, when "bytesWritten" signal is
  { qCDebug(drvPos) << tr("To write: %1").arg(byteArrayToHex(toSend.first(), bcoPrintable));
    printer->write(toSend.first()); //emitted, then process next one if any available.
  }
}
