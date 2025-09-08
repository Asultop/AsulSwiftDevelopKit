#include "T_Example.h"
#include "../Global/GlobalFunc.h"
#include "../Global/GlobalSettings.h"
#include "../SystemKit/AsulApplication.h"
#include "Def.h"


#include "ElaPushButton.h"
#include "ElaScrollPageArea.h"

T_Example::T_Example(QWidget *parent)
    : BaseScrollPage{parent}
{
    this->initWidget(tr("样例"),tr("样例"),tr(""));
    QVBoxLayout *centerVLayout=new QVBoxLayout(centralWidget);
    centerVLayout->setContentsMargins(0,20,20,20);
    ElaText *subtitle=new ElaText(tr("使用这个模板快速开始界面开发"),this);
    // subtitle->setMinimumWidth(200);

    centerVLayout->addWidget(GlobalFunc::GenerateArea(this,ElaIconType::GearCode,new ElaText("欢迎",this),subtitle,(QWidget*) nullptr));
    
    centerVLayout->addStretch();
}
