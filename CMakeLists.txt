cmake_minimum_required(VERSION 3.5)
project(vast LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt
find_package(Qt6 COMPONENTS Widgets QUIET)
if(NOT Qt6_FOUND)
  find_package(Qt5 REQUIRED COMPONENTS Widgets)
  set(QT_VERSION 5)
else()
  set(QT_VERSION 6)
endif()

if(QT_VERSION EQUAL 6)
  set(QT_LIBS Qt6::Widgets)
else()
  set(QT_LIBS Qt5::Widgets)
endif()

add_executable(vast src/main.cpp)

target_link_libraries(vast PRIVATE ${QT_LIBS})

target_include_directories(vast PUBLIC include)

install(TARGETS vast RUNTIME DESTINATION bin)
