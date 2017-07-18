cmake_minimum_required(VERSION 3.5.1)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

project(analizedir VERSION 0.1.1)
set(PROJECT_COMPANY_NAME "Avasoft")

set(CMAKE_CXX_FLAGS_COVERAGE "${CMAKE_CXX_FLAGS_RELEASE} -fprofile-arcs")
find_package(Qt5Core)
set_target_properties(Qt5::Core PROPERTIES MAP_IMPORTED_CONFIG_COVERAGE "RELEASE")


set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

set(SOURCES
    main.cpp
    robotsystem.cpp
    basic_helper.cpp
)


add_executable(analizedir ${SOURCES} )
target_link_libraries(analizedir Qt5::Core)
set(PROJECT_OUTPUT_NAME "analizedir")


set(EXECUTABLE_OUTPUT_PATH "/Users/dev/Applications/qt5.9.1/bin")

message(["EXECUTABLE_OUTPUT_PATH" ${EXECUTABLE_OUTPUT_PATH} )
message(["End line from cmakelist.txt ................ :-)")
