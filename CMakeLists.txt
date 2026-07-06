cmake_minimum_required(VERSION 4.0.0)

project(
    Unmatched
    LANGUAGES CXX
)

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
    src/Card.cpp
    src/Cell.cpp
    src/ReadInformation.cpp
    src/MapManager.cpp
    src/CardManager.cpp
)


target_link_libraries(app PUBLIC MyLibs)

target_include_directories(MyLibs PUBLIC "./include")