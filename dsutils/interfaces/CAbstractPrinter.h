#ifndef CABSTRACTPRINTER_H
#define CABSTRACTPRINTER_H

#include <QtCore/QList>
#include <QtCore/QMap>

#include "CAbstractMedia.h"

#include <CPosItem.hpp>

class CAbstractPrinter: public CAbstractMedia
{
  public:

    typedef       util::Callback<void (bool)> CbPrintDone;

    virtual       ~CAbstractPrinter() {}

    virtual void  printDocument(const CPosItem::List& pdData) = 0;
    virtual void  printerFeed(int nLines) = 0;
    virtual void  printerSendRaw(const QByteArray& baRaw) = 0;
    virtual void  setPrintDone(CbPrintDone cbPrint) = 0;

};

#define CAbstractPrinter_iid "posprn.delsoft.device"

Q_DECLARE_INTERFACE(CAbstractPrinter, CAbstractPrinter_iid)

#endif // CABSTRACTPRINTER_H
