cmake_minimum_required (VERSION 3.1.3)

project(leucht-server)

set(SOURCES
    src/main.cpp
    src/LeuchtAPI.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/external/pistache/include)

target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/external/pistache/lib/libpistache.a ssl crypto pthread)
