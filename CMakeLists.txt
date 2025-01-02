cmake_minimum_required(VERSION 3.20)

project(APCpp-Glue)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(CMAKE_SKIP_BUILD_RPATH  FALSE)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
SET(CMAKE_INSTALL_RPATH "$\{ORIGIN\}")

add_library(APCpp-Glue SHARED apcpp-glue.cpp apcpp-glue.h Archipelago.h)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(ENABLE_TESTING OFF CACHE BOOL "" FORCE)

set_target_properties(APCpp-Glue PROPERTIES PREFIX "")

include(FetchContent)
FetchContent_Declare(
    APCpp
    GIT_REPOSITORY https://github.com/RecompRando/APCpp.git
    GIT_TAG        main
)
FetchContent_MakeAvailable(APCpp)

if (WIN32)
    target_link_libraries(APCpp-Glue APCpp)
    target_link_libraries(APCpp-Glue ws2_32)
elseif(APPLE)
    target_link_libraries(APCpp-Glue APCpp)
else()
    target_link_libraries(APCpp-Glue APCpp)
endif(WIN32)