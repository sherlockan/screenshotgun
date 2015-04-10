#include "autostartup.h"
#include <QStandardPaths>
#include <QDir>
#include <QDebug>

AutoStartup::AutoStartup()
{
}

AutoStartup::~AutoStartup()
{
}

void AutoStartup::set(bool enabled)
{
#ifdef Q_OS_LINUX
    setLinux(enabled);
#endif
}

#ifdef Q_OS_LINUX
void AutoStartup::setLinux(bool enabled)
{
    QString autoStartPath = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation)
            + QLatin1String("/autostart/");

    QString desktopFileLocation = autoStartPath
            + "Screenshotgun"
            + QLatin1String(".desktop");

    if (enabled) {
        if (!QDir().exists(autoStartPath) && !QDir().mkpath(autoStartPath)) {
            qDebug() << "Could not create autostart directory";
            return;
        }

        QFile iniFile(desktopFileLocation);
        if (!iniFile.open(QIODevice::WriteOnly)) {
            qDebug() << "Could not write auto start entry" << desktopFileLocation;
            return;
        }

        QTextStream ts(&iniFile);
        ts.setCodec("UTF-8");
        ts << QLatin1String("[Desktop Entry]") << endl
           << QLatin1String("Name=") << "Screenshotgun" << endl
//           << QLatin1String("GenericName=") << QLatin1String("File Synchronizer") << endl
           << QLatin1String("Exec=") << QCoreApplication::applicationFilePath() << endl
           << QLatin1String("Terminal=") << "false" << endl
//           << QLatin1String("Icon=") << appName.toLower() << endl // always use lowercase for icons
           << QLatin1String("Categories=") << QLatin1String("Network") << endl
           << QLatin1String("Type=") << QLatin1String("Application") << endl
           << QLatin1String("StartupNotify=") << "false" << endl
           << QLatin1String("X-GNOME-Autostart-enabled=") << "true" << endl
            ;
    } else {
        if (!QFile::remove(desktopFileLocation)) {
            qDebug() << "Could not remove autostart desktop file";
        }
    }
}
#endif