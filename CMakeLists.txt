cmake_minimum_required(VERSION 3.16)
project(vast LANGUAGES CXX)

include(CPack)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CUDA_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(FFMPEG REQUIRED IMPORTED_TARGET libavformat libavcodec libavutil libswscale)
option(VAST_ENABLE_CUDA "Build CUDA accelerated detectors" ON)
find_package(CUDA)

include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.4.0
)
FetchContent_MakeAvailable(Catch2)


add_library(vast_lib
    src/MainWindow.cpp
    src/FrameLoader.cpp
    src/PluginManager.cpp
    src/ArtifactDetector.cpp
    src/ReportGenerator.cpp
)

if(VAST_ENABLE_CUDA AND CUDA_FOUND)
  target_sources(vast_lib PRIVATE src/detectors/blur_detector.cu)
  target_link_libraries(vast_lib PUBLIC CUDA::cuda_driver)
else()
  message(STATUS "CUDA not found - building without GPU detectors")
endif()

target_include_directories(vast_lib PUBLIC include)

target_link_libraries(vast_lib PUBLIC Qt6::Widgets PkgConfig::FFMPEG)

add_executable(vast
    src/main.cpp
)

target_link_libraries(vast PRIVATE vast_lib)

add_subdirectory(plugins/example)

install(TARGETS vast DESTINATION bin)
install(TARGETS vast_lib DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)

set(CPACK_GENERATOR "ZIP;TGZ")
set(CPACK_PACKAGE_NAME "VAST")
set(CPACK_PACKAGE_VERSION "0.1")
set(CPACK_PACKAGE_CONTACT "")
include(CPack)

enable_testing()
add_executable(vast_tests
    tests/test_frameloader.cpp
    tests/test_pluginmanager.cpp
)
target_link_libraries(vast_tests PRIVATE vast_lib Catch2::Catch2WithMain)
add_test(NAME vast_tests COMMAND vast_tests)
