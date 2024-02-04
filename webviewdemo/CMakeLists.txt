cmake_minimum_required(VERSION 3.16)

project(webviewdemo VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Quick WebView REQUIRED)

qt_add_executable(appwebviewdemo
    main.cpp
)

qt_add_qml_module(appwebviewdemo
    URI webviewdemo
    VERSION 1.0
    QML_FILES main.qml 
)

set_target_properties(appwebviewdemo PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_compile_definitions(appwebviewdemo
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(appwebviewdemo
    PRIVATE
    Qt6::Quick
    Qt6::WebView
)
