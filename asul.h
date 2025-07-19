#ifndef ASUL_H
#define ASUL_H

#include <ElaWindow.h>
#include "Sources/BaseInclude.h"

#define InstallPage(Label,Class,ElaIcon) \
    Class *Class##Page = new Class(); \
    this->addPageNode(Label, Class##Page, ElaIcon);

#define InstallFooter(Label,Class,_Key,ElaIcon) \
    Class *Class##FooterPage = new Class(); \
    this->addFooterNode(Label,Class##FooterPage,_Key,0,ElaIcon)

#define InstallAboutFooter(Class,_Key) \
    Class *Class##AboutPage = new Class(); \
    this->addFooterNode(tr("关于"),nullptr,_Key,0,ElaIconType::User); \
    connect(this,&ElaWindow::navigationNodeClicked,[=](ElaNavigationType::NavigationNodeType nodeType, QString nodeKey) { \
        Q_UNUSED(nodeType); \
        if (_Key == nodeKey) { \
            Class##AboutPage->moveToCenter(); \
            Class##AboutPage->show(); \
        } \
    });

class Asul : public ElaWindow
{
    Q_OBJECT

public:
    Asul(QWidget *parent = nullptr);
    ~Asul();
private:
    struct AsulINIT{
        bool userInfoCardVisible=true;
        QString userInfoCardPixmap;
        QString userInfoCardTitle;
        QString userInfoSubTitle;
        ElaAppBarType::ButtonFlags buttonFlags;
        AsulINIT(bool setUserInfoCardVisible=true
                 ,QString setUserInfoCardPixmap=""
                 ,QString setUserInfoCardTitle="Asul"
                 ,QString setUserInfoSubTitle="AsulKit"
                 ,ElaAppBarType::ButtonFlags buttonFlags={}
                 )
        {
            this->userInfoCardVisible=setUserInfoCardVisible;
            this->userInfoCardPixmap=setUserInfoCardPixmap;
            this->userInfoCardTitle=setUserInfoCardTitle;
            this->userInfoSubTitle=setUserInfoSubTitle;
            this->buttonFlags=buttonFlags;

        }
    };
    void AsulWindowINIT(ElaWindow * w,AsulINIT a){

        w->setUserInfoCardVisible(a.userInfoCardVisible);
        if(a.userInfoCardPixmap.contains("${THEME}")){
            w->setUserInfoCardPixmap(QString(a.userInfoCardPixmap).replace("${THEME}",eTheme->getThemeMode()==ElaThemeType::Dark?"dark":"light"));
            connect(eTheme,&ElaTheme::themeModeChanged,[=](ElaThemeType::ThemeMode themeMode){
                w->setUserInfoCardPixmap(QString(a.userInfoCardPixmap).replace("${THEME}",themeMode==ElaThemeType::Dark?"dark":"light"));
            });
        }else w->setUserInfoCardPixmap(a.userInfoCardPixmap);

        w->setUserInfoCardTitle(a.userInfoCardTitle);
        w->setUserInfoCardSubTitle(a.userInfoSubTitle);
        w->setWindowButtonFlags(a.buttonFlags);
    }
private:
    QString _setting,_about;

};

#endif // ASUL_H
