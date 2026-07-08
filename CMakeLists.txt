cmake_minimum_required(VERSION 3.24)
project(VkPhysDemo
    VERSION 1.0.0 
    LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

option(ENGINE_BUILD_APP "Build the executable" ON)
option(ENGINE_BUILD_SHARED "Build engine as shared lib" OFF)
option(ENGINE_ENABLE_TRACY "Enable tracy" OFF)

find_package(Vulkan REQUIRED)

add_subdirectory(external)
add_subdirectory(engine)

if(ENGINE_BUILD_APP)
    add_subdirectory(app)
endif()
