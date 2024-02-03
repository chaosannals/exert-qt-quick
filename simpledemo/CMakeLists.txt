cmake_minimum_required(VERSION 3.16)

project(simpledemo VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Quick Qml LinguistTools REQUIRED)

qt_add_executable(appsimpledemo
    main.cpp
)

qt_add_qml_module(appsimpledemo
    URI simpledemo
    VERSION 1.0
    QML_FILES main.qml Ball.qml
)

# 翻译(点构建时才会生成文件)
# 工具居然忽略了 qml 里 qsTr 需要翻译的文本 TODO
qt_add_translations(
    appsimpledemo
    RESOURCE_PREFIX
    /qt/qml/translated/i18n
    TS_FILES
    i18n/simpledemo_zh.ts
)


set_target_properties(appsimpledemo PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_compile_definitions(appsimpledemo
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(appsimpledemo
    PRIVATE Qt6::Quick)
