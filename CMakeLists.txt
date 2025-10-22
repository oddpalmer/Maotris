cmake_minimum_required(VERSION 4.0)
project(mygame)

set(CMAKE_CXX_STANDARD 20)
include_directories(./EasyX/include)
link_directories(./EasyX/lib64)
link_libraries(libeasyx.a)
add_executable(Maotris src/main.cpp
        src/Game.cpp
        include/Game.h
        src/Block.cpp
        include/Block.h
)
