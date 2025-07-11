cmake_minimum_required(VERSION 3.31)
project(smart_file_organizer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # Essential for C++20 features

set(CLI_EXECUTABLE_NAME "smart-file-organizer-cli")
set(GUI_EXECUTABLE_NAME "smart-file-organizer")
set(NLOHMANN_JSON_GIT "https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz")
set(SPDLOG_GIT "https://github.com/gabime/spdlog.git")
set(SPDLOG_GIT_TAG "v1.15.3")

# Define common source files for executables
set(SRC_FILES
        lib/common_lib.cpp
        lib/smart_rule.cpp)

# Fetch nlohmann/json
include(FetchContent)
FetchContent_Declare(nlohmann_json URL ${NLOHMANN_JSON_GIT})
FetchContent_MakeAvailable(nlohmann_json)

# include spdlog
FetchContent_Declare(spdlog GIT_REPOSITORY ${SPDLOG_GIT} GIT_TAG ${SPDLOG_GIT_TAG})
FetchContent_MakeAvailable(spdlog)

# set libs
set(COMMON_LIBS
        nlohmann_json::nlohmann_json
        spdlog::spdlog)

option(BUILD_WITH_GUI "Build with GUI version of the Smart File Organizer" OFF)

message(STATUS "Building CLI version of Smart File Organizer")

#BUILD CLI
add_executable(${CLI_EXECUTABLE_NAME} ${SRC_FILES} cli/cli_main.cpp)
target_link_libraries(${CLI_EXECUTABLE_NAME} PRIVATE ${COMMON_LIBS})

IF (BUILD_WITH_GUI)
    message(STATUS "Building GUI version of Smart File Organizer")
    #BUILD GUI
    add_executable(${GUI_EXECUTABLE_NAME} ${SRC_FILES} gui/gui_main.cpp)
    target_link_libraries(${GUI_EXECUTABLE_NAME} PRIVATE ${COMMON_LIBS})
ENDIF ()