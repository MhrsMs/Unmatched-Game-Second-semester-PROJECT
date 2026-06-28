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
    src/
)


target_link_libraries(app PUBLIC MyLibs)

target_include_directories(MyLibs PUBLIC "./include")