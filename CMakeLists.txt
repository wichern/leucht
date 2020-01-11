cmake_minimum_required (VERSION 3.5.1)

project(leucht-server)

set(SOURCES
    src/main.cpp
    src/LeuchtAPI.cpp
    src/Screen.cpp
    src/animation/AnimationBase.cpp
    src/animation/Plasma.cpp
    src/app/Default.cpp
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
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/external/pistache/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/external/bcm2835/src)

target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/external/pistache/lib/libpistache.a ssl crypto pthread SDL)
