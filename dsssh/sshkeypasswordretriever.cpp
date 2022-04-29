/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
****************************************************************************/

#include "sshkeypasswordretriever_p.h"

#include <QString>

#include <iostream>

namespace QSsh {
namespace Internal {

SshKeyPasswordRetriever::SshKeyPasswordRetriever(SshPasswordCall funcPassword)
  : Botan::User_Interface(), m_func(funcPassword)
{ }

std::string SshKeyPasswordRetriever::get_passphrase(const std::string &, const std::string &,
    UI_Result &result) const
{
    std::string password;

    if (m_func) {
      bool ok = false;

      password = m_func(ok).toStdString();
      result = ok ? OK : CANCEL_ACTION;
    } else { //Console will be used if no callback is defined
      result = OK;
      std::cout << "Please enter the password for your private key (set echo off beforehand!): " << std::flush;
      std::cin >> password;
    }
    return password;
}

} // namespace Internal
} // namespace QSsh
