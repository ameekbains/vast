cmake_minimum_required(VERSION 3.16)
project(vast LANGUAGES CXX CUDA)

include(CPack)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CUDA_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(FFMPEG REQUIRED IMPORTED_TARGET libavformat libavcodec libavutil libswscale)
find_package(CUDA REQUIRED)

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
    src/detectors/blur_detector.cu
)

target_include_directories(vast_lib PUBLIC include)

target_link_libraries(vast_lib PUBLIC Qt6::Widgets PkgConfig::FFMPEG CUDA::cuda_driver)

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
add_executable(vast_tests tests/test_frameloader.cpp)
target_link_libraries(vast_tests PRIVATE vast_lib Catch2::Catch2WithMain)
add_test(NAME vast_tests COMMAND vast_tests)
