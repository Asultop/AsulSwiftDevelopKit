#include "GlobalSettings.h"
#include "AsulApplication.h"
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
    this->setCharactersPerMinute(120);
    this->setGLoc(new QTemporaryDir());
    this->setEnableThemeColorSyncWithSystem(false);
    this->setEnableThemeModeSyncWithSystem(false);


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
