cmake_minimum_required(VERSION 3.16)
# include(FetchContent)

project(grpcdemo VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QT 的构造环境无法使用 grpc 官方的 cmake
# qt 自己做的设配又不支持 服务端，只做了客户端。
# TODO 做成 DLL ，又不跨平台。
# 引入 GRPC 项目
# FetchContent_Declare(
#   gRPC
#   # GIT_REPOSITORY https://github.com/grpc/grpc
#   GIT_REPOSITORY git@github.com:grpc/grpc.git
#   # GIT_REPOSITORY https://gitclone.com/github.com/grpc/grpc
#   GIT_TAG        v1.52.1
#   GIT_PROGRESS TRUE
# )
# FetchContent_MakeAvailable(gRPC)

find_package(Qt6 6.4 REQUIRED COMPONENTS  Protobuf Grpc Quick)

qt_standard_project_setup()

qt_add_executable(appgrpcdemo
    main.cpp
)

qt_add_qml_module(appgrpcdemo
    URI grpcdemo
    VERSION 1.0
    QML_FILES Main.qml
    SOURCES grpcbookdemoapi.h grpcbookdemoapi.cpp
)

qt_add_protobuf(appgrpcdemo
    PROTO_FILES
    ./protos/demo.proto
)

# QT 自带的 GRPC 库 只支持 客户端代码生成 SERVER 无效
qt_add_grpc(appgrpcdemo CLIENT
    PROTO_FILES
    ./protos/demo.proto
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appgrpcdemo PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appgrpcdemo
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appgrpcdemo
    PRIVATE
    Qt6::Quick
    Qt::Grpc
)

include(GNUInstallDirs)
install(TARGETS appgrpcdemo
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
