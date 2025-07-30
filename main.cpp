#include "asul.h"

#include <QApplication>
#include <ElaApplication.h>
#include <QStyleHints>
#include "Sources/COM_SplashWindow/T_SplashScreen.h"
#include "Sources/GlobalFunc.h"
#include "Sources/GlobalSettings.h"
#include "Sources/AsulApplication.h"
#include "Def.h"


#define QLOG_DEBUG qDebug

int main(int argc, char *argv[])
{

    AsulApplication a(argc, argv);
    eApp->init();

    gSets->init();
    //跟随系统主题色

    auto TranslationInstallation=[=](bool e){
        if(!e) return;
        QStringList SupportedLang=gSets->getSupportedLang();

        QString lang=gSets->getRegisterSettings()->value("lang").toString();
        if(!lang.isEmpty()){
            qApp->installTranslator(gSets->translators[lang]);
        }
    };
    TranslationInstallation(true);



    auto EnableSystemThemeColor=[=](bool e){
        if(!e) return;
        gSets->setEnableThemeColorSyncWithSystem(true);
        GlobalFunc::updateThemeUI();
    };

    //启用 启动细节面板
    T_SplashScreen *splashWindow=new T_SplashScreen(nullptr,gSets->getProgramName(),":/Sources/icon/splash_${THEME}.png");

    auto EnableSplashScreen = [splashWindow](bool e){
        if (!e) return;
        splashWindow->show();
    };
    a.processEvents();

    auto EnableSystemThemeMode=[=](bool e){
        if(!e) return;
        gSets->setEnableThemeModeSyncWithSystem(true);
    };
    auto CaptureScreenShotAndEnableMica=[=](bool e){
        if(!e) return;
        QScreen *screen = QGuiApplication::primaryScreen();
        QString filePath = gSets->getGLoc()->path()+"/mica.png";
        if (screen) {
            // 截取全屏幕图像
            QPixmap screenshot = screen->grabWindow(0);

            // 设置截图保存的文件名

            // 保存截图到文件
            if (screenshot.save(filePath, "PNG")) {
                // QLOG_DEBUG() << "[Mica] Screenshot saved as" << filePath;

            } else {
                // QLOG_DEBUG() << "[Mica] Failed to save screenshot";
            }
        }
        eApp->setElaMicaImagePath(filePath);

        // eApp->setWindowDisplayMode(ElaApplicationType::ElaMica);
    };



    //-------------------------------------
    EnableSystemThemeColor(false);
    EnableSystemThemeMode(false);
    EnableSplashScreen(true);
    CaptureScreenShotAndEnableMica(true);



    Asul w;
    w.show();

    QTimer::singleShot(200,[=](){
        splashWindow->close();
        splashWindow->disconnect();
        splashWindow->deleteLater();
    });

    return a.exec();
}

