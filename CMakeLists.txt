cmake_minimum_required(VERSION 3.16)
project(ASUL LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找Qt组件
find_package(Qt6 COMPONENTS Core Gui Network Widgets REQUIRED)
if(Qt6_FOUND)
    set(QT_LIBRARIES Qt6::Core Qt6::Gui Qt6::Network Qt6::Widgets)
else()
    find_package(Qt5 COMPONENTS Core Gui Network Widgets REQUIRED)
    set(QT_LIBRARIES Qt5::Core Qt5::Gui Qt5::Network Qt5::Widgets)
endif()

# 自动处理moc、uic和rcc
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# 源文件和头文件
set(SOURCES
    Sources/BaseScrollpage.cpp
    Sources/COM_HomeWidget/T_Home.cpp
    Sources/COM_SplashWindow/T_SplashScreen.cpp
    Sources/GlobalFunc.cpp
    Sources/GlobalSettings.cpp
    main.cpp
    asul.cpp
)

set(HEADERS
    Sources/BaseInclude.h
    Sources/BaseScrollpage.h
    Sources/COM_HomeWidget/T_Home.h
    Sources/COM_SplashWindow/T_SplashScreen.h
    Sources/GlobalFunc.h
    Sources/GlobalSettings.h
    asul.h
    singleton.h
    stdafx.h
)

# 资源文件
set(RESOURCES
    AsulKitSrc.qrc
)

# 添加资源文件
qt_add_resources(RESOURCE_FILES ${RESOURCES})

# 可执行文件
add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
    ${RESOURCE_FILES}
    Sources/AsulApplication.h Sources/AsulApplication.cpp
    Sources/COM_SettingWidget/T_SettingScreen.h Sources/COM_SettingWidget/T_SettingScreen.cpp

    Def.h
    Sources/COM_AboutWidget/T_About.h Sources/COM_AboutWidget/T_About.cpp

)

# 设置Windows资源文件
if(WIN32)
    set(RC_FILE ${CMAKE_CURRENT_SOURCE_DIR}/IDC/res.rc)
    set_source_files_properties(${RC_FILE} PROPERTIES LANGUAGE RC)
    target_sources(${PROJECT_NAME} PRIVATE ${RC_FILE})
endif()

# 包含目录
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/install/include
)

# 链接库
target_link_libraries(${PROJECT_NAME} PRIVATE
    ${QT_LIBRARIES}
)

# Windows特定设置
if(WIN32)
    # 链接ElaWidgetTools库
    if(MINGW)
        target_link_libraries(${PROJECT_NAME} PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/install/lib/libElaWidgetTools.a
        )
    else()
        target_link_libraries(${PROJECT_NAME} PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/install/lib/ElaWidgetTools.lib
        )
    endif()

    # 部署DLL
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/install/bin/ElaWidgetTools.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
        COMMENT "Copying ElaWidgetTools.dll to binary directory"
    )
endif()

# 安装设置
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)
