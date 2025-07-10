cmake_minimum_required(VERSION 3.31)
project(smart_file_organizer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # Essential for C++20 features

set(CLI_EXECUTABLE_NAME "smart-file-organizer-cli")
set(GUI_EXECUTABLE_NAME "smart-file-organizer")

# Fetch nlohmann/json
include(FetchContent)
FetchContent_Declare(nlohmann_json URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz)
FetchContent_MakeAvailable(nlohmann_json)

option(BUILD_WITH_GUI "Build with GUI version of the Smart File Organizer" OFF)

message(STATUS "Building CLI version of Smart File Organizer")


#BUILD CLI
add_executable(${CLI_EXECUTABLE_NAME} lib/common_lib.cpp lib/smart_rule.cpp cli/cli_main.cpp)
target_link_libraries(${CLI_EXECUTABLE_NAME} PRIVATE nlohmann_json::nlohmann_json)
# Critical for header-only lib
target_include_directories(${CLI_EXECUTABLE_NAME} PRIVATE ${nlohmann_json_SOURCE_DIR})


IF (BUILD_WITH_GUI)
    message(STATUS "Building GUI version of Smart File Organizer")
    #BUILD GUI
    add_executable(${GUI_EXECUTABLE_NAME} lib/common_lib.cpp lib/smart_rule.cpp gui/gui_main.cpp)
    target_link_libraries(${GUI_EXECUTABLE_NAME} PRIVATE nlohmann_json::nlohmann_json)
ENDIF ()

