cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
project(super2048)

# Dependencies


find_library(RAYLIB raylib "${CMAKE_PREFIX_PATH}/lib")

# target_include_directories()
# Our Project
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp") 

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_PREFIX_PATH}/include")

target_link_libraries(${PROJECT_NAME} PRIVATE ${RAYLIB})

if (WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE winmm.lib)
endif()


# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()