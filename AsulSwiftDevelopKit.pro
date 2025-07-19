QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

RC_FILE += IDC/res.rc
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Sources/BaseScrollpage.cpp \
    Sources/COM_HomeWidget/T_Home.cpp \
    Sources/COM_SplashWindow/T_SplashScreen.cpp \
    Sources/GlobalFunc.cpp \
    Sources/GlobalSettings.cpp \
    main.cpp \
    asul.cpp

HEADERS += \
    Sources/BaseInclude.h \
    Sources/BaseScrollpage.h \
    Sources/COM_HomeWidget/T_Home.h \
    Sources/COM_SplashWindow/T_SplashScreen.h \
    Sources/GlobalFunc.h \
    Sources/GlobalSettings.h \
    asul.h \
    singleton.h \
    stdafx.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


win32 {
    # 源DLL路径（根据实际情况调整）
    DLL_SOURCE = $${PWD}/install/bin/ElaWidgetTools.dll
    DLL_SOURCE = $$replace(DLL_SOURCE, /, \\)
    # 目标目录（与exe同级）
    DLL_TARGET = $${OUT_PWD}/release/
    DLL_TARGET = $$replace(DLL_TARGET, /, \\)

    # 构建后执行复制命令
    build_pass:system(copy /Y $$DLL_SOURCE $$DLL_TARGET)
    build_pass:message("DLL_SOURCE: " $$DLL_SOURCE)
    build_pass:message("DLL_TARGET: " $$DLL_TARGET)
}

win32: LIBS += -L$$PWD/install/lib/ -lElaWidgetTools
INCLUDEPATH += $$PWD/install/include
DEPENDPATH += $$PWD/install/include

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/install/lib/ElaWidgetTools.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/install/lib/libElaWidgetTools.a

RESOURCES += \
    AsulKitSrc.qrc
