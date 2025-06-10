cmake_minimum_required(VERSION 3.16)
project(vast LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

add_library(vast_lib
    src/MainWindow.cpp
    src/FrameLoader.cpp
    src/PluginManager.cpp
    src/ArtifactDetector.cpp
)

target_include_directories(vast_lib PUBLIC include)

target_link_libraries(vast_lib PUBLIC Qt6::Widgets)

add_executable(vast
    src/main.cpp
)

target_link_libraries(vast PRIVATE vast_lib)
