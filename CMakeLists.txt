cmake_minimum_required(VERSION 3.29)
project(ECS)

set(CMAKE_CXX_STANDARD 20)

add_executable(ECS main.cpp
        Entity.cpp
        Entity.h
        EntityManager.cpp
        EntityManager.h
        GameEngine.cpp
        GameEngine.h)
