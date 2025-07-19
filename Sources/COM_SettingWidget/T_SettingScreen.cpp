#include "T_SettingScreen.h"
#include "../GlobalFunc.h"
#include "../GlobalSettings.h"
#include <ElaToggleSwitch.h>
#include <qboxlayout.h>
#include <qpixmap.h>
#include <qstylehints.h>
#include "../AsulApplication.h"
#include "Def.h"
#include "ElaApplication.h"
#include "ElaComboBox.h"
#include "ElaColorDialog.h"
#include "ElaPlainTextEdit.h"
#include "ElaPushButton.h"
#include "ElaScrollPageArea.h"

T_SettingScreen::T_SettingScreen(QWidget *parent)
    : BaseScrollPage{parent}
{
    this->initWidget(tr("Setting"),tr("Setting"),tr(""));


    QVBoxLayout *centerVLayout=new QVBoxLayout(centralWidget);

    ElaToggleSwitch *closeThemeColorSync=new ElaToggleSwitch(this);
    closeThemeColorSync->setIsToggled(gSets->getEnableThemeColorSyncWithSystem());
    centerVLayout->addWidget(GlobalFunc::GenerateArea(this,new ElaText(tr("开启颜色同步"),this),new ElaText(tr("同步 Windows 的主题色"),this),closeThemeColorSync,false));
    connect(closeThemeColorSync,&ElaToggleSwitch::toggled,[=](bool checked){
        gSets->setEnableThemeColorSyncWithSystem(checked);
        if(checked) GlobalFunc::updateThemeUI();
    });

    ElaToggleSwitch *closeThemeModeSync=new ElaToggleSwitch(this);
    closeThemeModeSync->setIsToggled(gSets->getEnableThemeModeSyncWithSystem());
    centerVLayout->addWidget(GlobalFunc::GenerateArea(this,new ElaText(tr("开启明暗同步"),this),new ElaText(tr("同步 Windows 的明暗模式"),this),closeThemeModeSync,false));
    connect(closeThemeModeSync,&ElaToggleSwitch::toggled,[=](bool checked){
        gSets->setEnableThemeModeSyncWithSystem(checked);
        if(checked){
            Qt::ColorScheme scheme = qApp->styleHints()->colorScheme();
            if(scheme == Qt::ColorScheme::Dark){
                eTheme->setThemeMode(ElaThemeType::Dark);
            }else eTheme->setThemeMode(ElaThemeType::Light);
        }
    });

    ElaComboBox *SwitchDisplayMode=new ElaComboBox(this);
    SwitchDisplayMode->addItems(QString{"Normal ElaMica Mica MicaAlt Acrylic DWMBlur"}.split(" "));
    centerVLayout->addWidget(GlobalFunc::GenerateArea(this,new ElaText(tr("显示模式"),this),new ElaText(tr("切换窗口显示模式"),this),SwitchDisplayMode,false));
    connect(SwitchDisplayMode,&ElaComboBox::currentIndexChanged,[=](int index){
        QString filePath = gSets->getGLoc()->path()+"/mica.png";
        switch (index){
            case 0:
                // eApp->setElaMicaImagePath(filePath);
                eApp->setWindowDisplayMode(ElaApplicationType::Normal);
                break;
            case 1:
                // eApp->setElaMicaImagePath(filePath);
                eApp->setWindowDisplayMode(ElaApplicationType::ElaMica);
                break;
            case 2:
                // eApp->setElaMicaImagePath(filePath);
                eApp->setWindowDisplayMode(ElaApplicationType::Mica);
                break;
            case 3:
                // eApp->setElaMicaImagePath(filePath);
                eApp->setWindowDisplayMode(ElaApplicationType::MicaAlt);
                break;
            case 4:
                // eApp->setElaMicaImagePath(filePath);
                eApp->setWindowDisplayMode(ElaApplicationType::Acrylic);
                break;
            case 5:
                // eApp->setElaMicaImagePath(filePath);
                eApp->setWindowDisplayMode(ElaApplicationType::DWMBlur);
                break;
        }
    });

    //切换主题
    ElaComboBox * changeThemeMode = new ElaComboBox(this);
    changeThemeMode->addItems(QString{"Light Dark"}.split(" "));
    centerVLayout->addWidget(GlobalFunc::GenerateArea(this,new ElaText(tr("切换主题"),this),new ElaText(tr("切换 Dark/Light"),this),changeThemeMode,false));
    connect(changeThemeMode,&ElaComboBox::currentIndexChanged,[=](int index){
        if(index==0){
            eTheme->setThemeMode(ElaThemeType::Light);
        }else eTheme->setThemeMode(ElaThemeType::Dark);
    });

    ElaPushButton * ColorPickBtn=new ElaPushButton(this);

    ElaColorDialog * colorDialog=new ElaColorDialog(this);

    GlobalFunc::addThemeSyncList(ColorPickBtn);
    ColorPickBtn->setText(tr("选择颜色"));

    colorDialog->setWindowTitle(" ");
    connect(ColorPickBtn,&ElaPushButton::clicked,[=](){
        // qDebug()<<"ColorPick Clicked"<<Qt::endl;
        colorDialog->exec();
    });
    connect(colorDialog, &ElaColorDialog::colorSelected, this, [=](const QColor& color) {
        GlobalFunc::updateThemeUI(color);
    });
    centerVLayout->addWidget(GlobalFunc::GenerateArea(this,ElaIconType::Display,new ElaText(tr("选择颜色"),this),new ElaText(tr("选择自定义颜色"),this),ColorPickBtn,false));


    ElaComboBox *test1ComboBox=new ElaComboBox(this);
    test1ComboBox->addItems(QString{"Test1 Test2 Test3 Test4 Test5"}.split(" "));
    centerVLayout->addWidget(GlobalFunc::GenerateArea(this,ElaIconType::DiceD6,new ElaText(tr("测试图标"),this),new ElaText(tr("测试图标"),this),test1ComboBox,false));

    ElaComboBox *test2ComboBox=new ElaComboBox(this);
    test2ComboBox->addItems(QString{"Test1 Test2 Test3 Test4 Test5"}.split(" "));
    centerVLayout->addWidget(GlobalFunc::GenerateArea(this,QString(":/Sources/icon/splash_${THEME}.png"),new ElaText(tr("测试图标"),this),new ElaText(tr("测试图标"),this),test2ComboBox,false));
    
    
    ElaScrollPageArea * TestingArea=new ElaScrollPageArea(this);
    TestingArea->setMinimumWidth(600);
    ElaPlainTextEdit *TestingAreaTextEdit=new ElaPlainTextEdit(this);
    TestingAreaTextEdit->setPlainText("TestingAreaTextEdit");
    QHBoxLayout *testingAreaLayout=new QHBoxLayout(TestingArea);
    testingAreaLayout->addWidget(TestingAreaTextEdit);
    centerVLayout->addWidget(TestingArea);


    centerVLayout->addStretch();
}
