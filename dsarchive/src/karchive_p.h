/* This file is part of the KDE libraries
   Copyright (C) 2000-2005 David Faure <faure@kde.org>
   Copyright (C) 2003 Leo Savernik <l.savernik@aon.at>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#ifndef KARCHIVE_P_H
#define KARCHIVE_P_H

#include "karchive.h"

#include <qsavefile.h>

class KArchivePrivate
{
    Q_DECLARE_TR_FUNCTIONS(KArchivePrivate)

public:
    KArchivePrivate()
        : rootDir(nullptr)
        , saveFile(nullptr)
        , dev(nullptr)
        , fileName()
        , mode(QIODevice::NotOpen)
        , deviceOwned(false)
    {
    }
    ~KArchivePrivate()
    {
        delete saveFile;
        delete rootDir;
    }
    void abortWriting();

    static QDateTime time_tToDateTime(uint time_t);

    KArchiveDirectory *rootDir;
    QSaveFile *saveFile;
    QIODevice *dev;
    QString fileName;
    QIODevice::OpenMode mode;
    bool deviceOwned; // if true, we (KArchive) own dev and must delete it
    QString errorStr{tr("Unknown error")};
};

#if (QT_VERSION >= QT_VERSION_CHECK(5, 10, 0))
#define secsSinceEpoc()   toSecsSinceEpoch()
#define fromSecsSince(t)  fromSecsSinceEpoch(t)
#define birth             birthTime
#else
#define secsSinceEpoc()   toMSecsSinceEpoch()/1000
#define fromSecsSince(t)  fromMSecsSinceEpoch(t*1000)
#define birth             created
#endif

#endif // KARCHIVE_P_H
