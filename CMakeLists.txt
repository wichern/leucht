cmake_minimum_required (VERSION 3.5.1)

set(CMAKE_C_COMPILER_WORKS)
project(leucht-server)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    src/main.cpp
    src/LeuchtAPI.cpp
    src/Screen.cpp
    src/animation/AnimationBase.cpp
    src/animation/Plasma.cpp
    src/app/Welcome.cpp
    src/app/Colour.cpp
    src/app/Snake.cpp
    src/app/Clock.cpp
    src/app/Radio.cpp
    src/engine/Renderer.cpp
    src/engine/Game.cpp

    external/bcm2835/src/bcm2835.c
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/external/bcm2835/src)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/external/pistache/include)

if(CMAKE_CROSSCOMPILING)
    target_link_libraries(${PROJECT_NAME} pistache pthread)
else()
    add_definitions(-DSDL_RENDERING)
    target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/external/pistache/lib/libpistache.a ssl crypto pthread SDL)
endif()

