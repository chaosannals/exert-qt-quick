cmake_minimum_required(VERSION 3.16)

project(cppNqml VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Quick Qml LinguistTools REQUIRED)

qt_add_executable(appcppNqml
    main.cpp
    segmentdemo.cpp
)

qt_add_qml_module(appcppNqml
    URI cppNqml
    VERSION 1.0
    QML_FILES main.qml 
)

qt_add_translations(
    appcppNqml
    SOURCES
    ${PROJECT_SOURCES}
    RESOURCE_PREFIX
    /qt/qml/translated/i18n
    TS_FILES
    i18n/cppNqml_zh.ts
)

set_target_properties(appcppNqml PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_compile_definitions(appcppNqml
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(appcppNqml
    PRIVATE Qt6::Quick)
