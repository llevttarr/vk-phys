cmake_minimum_required(VERSION 3.24)
project(VkPhysDemo
    VERSION 1.0.0 
    LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(phys_demo 
    src/main.cpp 
)

target_include_directories(phys_demo PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
)
