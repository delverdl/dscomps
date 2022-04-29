#ifndef CPOSPRINTER_H
#define CPOSPRINTER_H

#include <interfaces/CAbstractPrinter>

#include <QLoggingCategory>
#include <QSerialPort>
#include <QTcpSocket>

Q_DECLARE_LOGGING_CATEGORY(drvPos)

class CPosPrinter :
    public QObject,
    public CAbstractPrinter
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID CAbstractPrinter_iid FILE "dsposprn.json")
    Q_INTERFACES(CAbstractPrinter)

  public:
    CPosPrinter(QObject *parent = nullptr);
    ~CPosPrinter();

    virtual void      openMedia(const QString& sDevice);
    virtual void      openMedia(QIODevice* bus);
    virtual void      closeMedia();

    virtual void      setStatusReport(CbDeviceStatus ds);

    virtual void      printDocument(const CPosItem::List& pdData);
    virtual void      printerFeed(int nLines);
    virtual void      printerSendRaw(const QByteArray& baRaw);
    virtual void      setPrintDone(CbPrintDone cbPrint);

  private:
    QIODevice*        printer;
    CbDeviceStatus    deviceStatus;
    CbPrintDone       printDone;
    CPosItem::Packets toSend;
    bool              isConnected;
    bool              isExternal;
    bool              isSerial;

    void              checkDeviceError(int nError, bool bTcp = false);
    void              emitStatus(DeviceStatus de);
    void              emitPrintDone(bool b = true);
    void              releaseMemory();
    bool              isReady();

  private slots:
    //Device
    void              bytesWritten(qint64 bytes);
    void              socketError(QAbstractSocket::SocketError error);
    void              socketConnected();
    void              socketDisconnected();

    //Internal
    void              writePacket();

};

#endif // CPOSPRINTER_H
