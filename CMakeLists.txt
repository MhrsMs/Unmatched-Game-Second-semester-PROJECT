cmake_minimum_required(VERSION 3.20)  

project(
    Unmatched
    LANGUAGES CXX C
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(external/raylib)

add_executable(
    app main.cpp
)

add_library(
    MyLibs STATIC 
    src/Hero.cpp
    src/Dracula.cpp
    src/Sister.cpp
    src/Sherlock.cpp
    src/DrWatson.cpp
    src/InvisibleMan.cpp
    src/Card.cpp
    src/Cell.cpp
    src/ReadInformation.cpp
    src/MapManager.cpp
    src/CardManager.cpp
    src/ConsoleView.cpp
    src/Effect.cpp
    src/GameManager.cpp
    src/Action.cpp
    src/Attack.cpp
    src/Maneuver.cpp
    src/PlayerInformation.cpp
    src/Scheme.cpp
    src/InputNumber.cpp
    src/FirstMenu.cpp
)

target_link_libraries(app PUBLIC MyLibs)

target_link_libraries(MyLibs PUBLIC raylib)

target_include_directories(MyLibs PUBLIC "./include")
