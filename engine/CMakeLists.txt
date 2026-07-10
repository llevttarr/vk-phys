file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
)

set(ENGINE_LIB_TYPE STATIC)
if(ENGINE_BUILD_SHARED)
    set(ENGINE_LIB_TYPE SHARED)
endif()

add_library(engine ${ENGINE_LIB_TYPE} ${ENGINE_SOURCES})

file(GLOB_RECURSE ENGINE_SRC_SUBDIRS LIST_DIRECTORIES true CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*
)
set(ENGINE_PRIVATE_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/src)
foreach(DIR ${ENGINE_SRC_SUBDIRS})
    if(IS_DIRECTORY ${DIR})
        list(APPEND ENGINE_PRIVATE_INCLUDE_DIRS ${DIR})
    endif()
endforeach()

target_include_directories(engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
file(GLOB_RECURSE ENGINE_INTERNAL_INCLUDE_SUBDIRS
    LIST_DIRECTORIES true CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/engine/*
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*
)

set(ENGINE_PRIVATE_INCLUDE_DIRS "")
foreach(DIR ${ENGINE_INTERNAL_INCLUDE_SUBDIRS})
    if(IS_DIRECTORY ${DIR})
        list(APPEND ENGINE_PRIVATE_INCLUDE_DIRS ${DIR})
    endif()
endforeach()

target_include_directories(engine PRIVATE
    ${ENGINE_PRIVATE_INCLUDE_DIRS}
)
target_link_libraries(engine
    PUBLIC
        Vulkan::Vulkan
        volk
        GPUOpen::VulkanMemoryAllocator
        glm::glm
        glfw
    PRIVATE
        imgui
        stb
        assimp
        meshoptimizer
        Jolt
)

if(ENGINE_ENABLE_TRACY)
    target_link_libraries(engine PUBLIC Tracy::TracyClient)
    target_compile_definitions(engine PUBLIC TRACY_ENABLE)
endif()

target_compile_definitions(engine PUBLIC
    GLFW_INCLUDE_NONE
)
