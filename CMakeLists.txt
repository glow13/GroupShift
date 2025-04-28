cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if ("${CMAKE_SYSTEM_NAME}" STREQUAL "iOS" OR IOS)
    set(CMAKE_OSX_ARCHITECTURES "arm64")
else()
    set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")
endif()
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

project(GroupShift VERSION 1.1.1)

# Set up the mod binary
add_library(${PROJECT_NAME} SHARED
    src/fixes/InstantCountEditFix.cpp

    src/popups/ShiftPopup.cpp
    src/popups/GroupShiftPopup.cpp
    src/popups/PropertyShiftPopup.cpp

    src/overrides/CollisionBlockPopup.cpp
    src/overrides/ColorSelectPopup.cpp
    src/overrides/SetGroupIDLayer.cpp
    src/overrides/SetItemIDLayer.cpp
    src/overrides/SetupCollisionTriggerPopup.cpp
    src/overrides/SetupCountTriggerPopup.cpp
    src/overrides/SetupInstantCollisionTriggerPopup.cpp
    src/overrides/SetupInstantCountPopup.cpp
    src/overrides/SetupItemCompareTriggerPopup.cpp
    src/overrides/SetupItemEditTriggerPopup.cpp
    src/overrides/SetupMoveCommandPopup.cpp
    src/overrides/SetupObjectTogglePopup.cpp
    src/overrides/SetupOpacityPopup.cpp
    src/overrides/SetupPickupTriggerPopup.cpp
    src/overrides/SetupSpawnPopup.cpp

    # Add any extra C++ source files here
)

if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK! Please define GEODE_SDK environment variable to point to Geode")
else()
    message(STATUS "Found Geode: $ENV{GEODE_SDK}")
endif()

add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Set up dependencies, resources, and link Geode.
setup_geode_mod(${PROJECT_NAME})
