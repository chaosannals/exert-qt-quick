cmake_minimum_required(VERSION 3.16)

project(webenginedemo VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# WebEngineWidgets 是给手机端 android 和 ios 的组件
find_package(Qt6 6.2 COMPONENTS Quick REQUIRED)

qt_add_executable(appwebenginedemo
    main.cpp
)

qt_add_qml_module(appwebenginedemo
    URI webenginedemo
    VERSION 1.0
    QML_FILES main.qml 
)

set_target_properties(appwebenginedemo PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_compile_definitions(appwebenginedemo
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(appwebenginedemo
    PRIVATE
    Qt6::Quick
    # WebEngineWidgets 是给手机端 android 和 ios 的组件
#    Qt6::WebEngineWidgets
)
