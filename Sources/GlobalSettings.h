#ifndef GLOBALSETTINGS_H
#define GLOBALSETTINGS_H

#include <QObject>
#include "stdafx.h"
#include "singleton.h"
#include <QTemporaryDir>
#define gSets GlobalSettings::getInstance()
class GlobalSettings : public QObject
{
    Q_OBJECT
    Q_SINGLETON_CREATE_H(GlobalSettings);
    Q_PROPERTY_CREATE(qint64,QINT64_Example);
    Q_PROPERTY_CREATE(int,CharactersPerMinute);
    Q_PROPERTY_CREATE(QTemporaryDir*,GLoc);

    Q_PROPERTY_CREATE(bool,EnableThemeColorSyncWithSystem);
    Q_PROPERTY_CREATE(bool,EnableThemeModeSyncWithSystem);
    Q_PROPERTY_CREATE(QString,EnableDisplayMode);
public:
    explicit GlobalSettings(QObject *parent = nullptr);
    void init();
    void destroy();
signals:
};

#endif // GLOBALSETTINGS_H
