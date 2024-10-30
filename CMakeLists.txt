cmake_minimum_required(VERSION 3.15)

# ==================================================
# Project

project(
    AyTest_Mini
    VERSION 0.3.0
    LANGUAGES CXX
)

# Module: namespace::name
set(MODULE_NAME aytestm)
set(MODULE_NS ayin)

# ==================================================

# Init cmake environment
include(cmake/Init.cmake)

# ==================================================
# Module library

add_library(${MODULE_NAME} INTERFACE)
target_include_directories(${MODULE_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(${MODULE_NS}::${MODULE_NAME} ALIAS ${MODULE_NAME})
message(STATUS "Build library `${MODULE_NS}::${MODULE_NAME}`")

# ==================================================
# Project development environment 

if(${PROJECT_NAME}_IS_MAIN)
    # Main
    add_subdirectory(main)
endif()
