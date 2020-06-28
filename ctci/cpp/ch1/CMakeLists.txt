cmake_minimum_required(VERSION 3.10.2)
project(ch1_ctci)
add_library(Ch1_ctci STATIC
    dynamicArray.cpp
    hashTable.cpp)
target_link_libraries(Ch1_ctci PUBLIC Common)
add_executable(Ch1_ctci_main main.cpp)
target_link_libraries(Ch1_ctci_main Ch1_ctci)
