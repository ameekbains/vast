add_library(example_detector SHARED example_detector.cpp)

target_include_directories(example_detector PRIVATE ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(example_detector PRIVATE Qt6::Widgets)

set_target_properties(example_detector PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/plugins
)
install(TARGETS example_detector DESTINATION plugins)
