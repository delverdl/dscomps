//
// C++ Interface: colormodel
//
// Description:
//
//
// Author: Witold Wysota <wysota@wysota.eu.org>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef COLORMODEL_H
#define COLORMODEL_H

#include <QStandardItemModel>
#include <QColor>
#include <QString>
#include <wwglobal.h>

/**
 *  @internal
 *
 */
class Q_WW_EXPORT ColorModel : public QStandardItemModel {
public:
    ColorModel(QObject *parent=0);
    QModelIndex contains(const QColor &c);
    ColorModel *clone(QObject *par=0) const;
    QModelIndex addColor(const QColor &c, const QString &name=QString());
    QModelIndex insertColor(int index, const QColor &c, const QString &name=QString());
};

#endif
