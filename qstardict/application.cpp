/*****************************************************************************
 * application.cpp - QStarDict, a StarDict clone written with using Qt       *
 * Copyright (C) 2008 Alexander Rodin                                        *
 *                                                                           *
 * This program is free software; you can redistribute it and/or modify      *
 * it under the terms of the GNU General Public License as published by      *
 * the Free Software Foundation; either version 2 of the License, or         *
 * (at your option) any later version.                                       *
 *                                                                           *
 * This program is distributed in the hope that it will be useful,           *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 * GNU General Public License for more details.                              *
 *                                                                           *
 * You should have received a copy of the GNU General Public License along   *
 * with this program; if not, write to the Free Software Foundation, Inc.,   *
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.               *
 *****************************************************************************/

#include "application.h"

#ifdef QSTARDICT_WITH_TRANSLATIONS
#include <QLocale>
#include <QTranslator>
#endif // QSTARDICT_WITH_TRANSLATIONS
#include "dictcore.h"
#include "mainwindow.h"
#include "popupwindow.h"
#include "trayicon.h"
#ifdef QSTARDICT_WITH_DBUS
#include "dbusadaptor.h"
#endif // QSTARDICT_WITH_DBUS

namespace QStarDict
{

Application::Application(int &argc, char **argv)
    : QApplication(argc, argv)
{
    setOrganizationName("qstardict");
    setApplicationName("qstardict");

#ifdef QSTARDICT_WITH_TRANSLATIONS
    m_translator = new QTranslator;
    m_translator->load(QSTARDICT_TRANSLATIONS_DIR "/qstardict-" + QLocale::system().name());
    installTranslator(m_translator);
#endif // QSTARDICT_WITH_TRANSLATIONS

    m_dictCore = new DictCore;
    m_popupWindow = new PopupWindow;
    m_popupWindow->setDict(m_dictCore);
    m_mainWindow = new MainWindow;
    m_mainWindow->setDict(m_dictCore);
    m_trayIcon = new TrayIcon;
#ifdef QSTARDICT_WITH_DBUS
    m_dbusAdaptor = new DBusAdaptor(m_mainWindow);
#endif // QSTARDICT_WITH_DBUS
}

Application::~Application()
{
    delete m_trayIcon;
    delete m_mainWindow;
    delete m_popupWindow;
    delete m_dictCore;
#ifdef QSTARDICT_WITH_TRANSLATIONS
    removeTranslator(m_translator);
    delete m_translator;
#endif // QSTARDICT_WITH_TRANSLATIONS
}

int Application::exec()
{
    m_trayIcon->show();
    m_mainWindow->show();
    return QApplication::exec();
}

}

// vim: tabstop=4 softtabstop=4 shiftwidth=4 expandtab cindent textwidth=120 formatoptions=tc
