/*
 * Copyright (C) 2018 Canonical, Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "process_spec.h"

#include <QFileInfo>

namespace mp = multipass;

// Create Process with these fixed arguments. Other optional arguments can be appended in Process::start()
QStringList mp::ProcessSpec::arguments() const
{
    return QStringList();
}

// Set environment of child as that of this process
QProcessEnvironment multipass::ProcessSpec::environment() const
{
    return QProcessEnvironment::systemEnvironment();
}

// For cases when multiple instances of this process need different apparmor profiles, use this
// identifier to distinguish them
QString multipass::ProcessSpec::identifier() const
{
    return QString();
}

const QString mp::ProcessSpec::apparmor_profile_name() const
{
    const QString executable_name = QFileInfo(program()).fileName(); // in case full path is specified

    if (!identifier().isNull())
    {
        return QStringLiteral("multipass.") + identifier() + '.' + executable_name;
    }
    else
    {
        return QStringLiteral("multipass.") + executable_name;
    }
}

// Commands here are run after fork() and before execve(), allowing drop of privileges, etc.
void mp::ProcessSpec::setup_child_process() const
{
    // Example: Drop all privileges in the child process, and enter a chroot jail.
    //     ::setgroups(0, 0);
    //     ::chroot("/etc/safe");
    //     ::chdir("/");
    //     ::setgid(safeGid);
    //     ::setuid(safeUid);
    //     ::umask(0);
}
