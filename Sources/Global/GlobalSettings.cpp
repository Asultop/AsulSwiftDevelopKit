#include "GlobalSettings.h"
#include "../SystemKit/AsulApplication.h"
#include <QStyleHints>
#include <ElaTheme.h>
#include "GlobalFunc.h"
#include <ElaPushButton.h>
#include <ElaLineEdit.h>
#include <ElaText.h>

Q_SINGLETON_CREATE_CPP(GlobalSettings);
GlobalSettings::GlobalSettings(QObject *parent)
    : QObject{parent}{}

void GlobalSettings::init()
{
    QFile programJson(":/PropertySetting/Program_Property.json");
    if(programJson.open(QIODevice::ReadOnly)){
        QByteArray data = programJson.readAll();
        programJson.close();
        QJsonParseError parseError;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data, &parseError);
        jsonObj = jsonDoc.object();
    }


    this->setCharactersPerMinute(120);
    this->setGLoc(new QTemporaryDir());
    this->setEnableThemeColorSyncWithSystem(false);
    this->setEnableThemeModeSyncWithSystem(false);
    this->setSupportedLang(QStringList{"zh_CN","en_US"});


    foreach(QString lang,this->getSupportedLang()){
        translators[lang] = new QTranslator(this);
        translators[lang]->load(QString(":/translations/AsulKit_%1.qm").arg(lang));
    }


    this->setRegisterSettings(new QSettings(getProgramOrganization(),getProgramName(),this));

    Qt::ColorScheme scheme = qApp->styleHints()->colorScheme();
    if(scheme == Qt::ColorScheme::Dark){
        eTheme->setThemeMode(ElaThemeType::Dark);
    }else eTheme->setThemeMode(ElaThemeType::Light);

    connect(qApp->styleHints(),&QStyleHints::colorSchemeChanged,[=](){
        if(!this->getEnableThemeModeSyncWithSystem()) return;

        Qt::ColorScheme scheme = qApp->styleHints()->colorScheme();
        if(scheme == Qt::ColorScheme::Dark){
            eTheme->setThemeMode(ElaThemeType::Dark);
        }else eTheme->setThemeMode(ElaThemeType::Light);
        GlobalFunc::updateThemeUI();
    });
    connect(aApp,&AsulApplication::themeChanged,[=](){
        GlobalFunc::updateThemeUI();
    });

}
void GlobalSettings::destroy(){

    delete this->getGLoc();
}

QString GlobalSettings::getProgramName()
{
    return jsonObj["programName"].toString();
}

QString GlobalSettings::getProgramVersion()
{
    return jsonObj["programVersion"].toString();
}

QString GlobalSettings::getProgramDescription()
{
    return jsonObj["programDescription"].toString();
}

QString GlobalSettings::getProgramAuthor()
{
    return jsonObj["programAuthor"].toString();
}

QString GlobalSettings::getProgramLicense()
{
    return jsonObj["programLicense"].toString();
}

QString GlobalSettings::getProgramRepository()
{
    return jsonObj["programRepository"].toString();
}

QString GlobalSettings::getProgramOrganization()
{
    return jsonObj["programOrganization"].toString();
}
