cmake_minimum_required(VERSION 3.0)
SET (CMAKE_CXX_COMPILER "/usr/bin/clang++")
SET (CMAKE_CXX_FLAGS "-Wall")

project(Planner)

find_package(Eigen3 REQUIRED)

add_library(plannerlib SHARED libVehicleModel.cpp)

add_executable(main main.cpp)

install(TARGETS plannerlib DESTINATION /usr/lib)

