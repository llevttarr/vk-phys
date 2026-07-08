file(GLOB_RECURSE DEMO_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_executable(demo ${DEMO_SOURCES})
target_link_libraries(demo PRIVATE engine)

add_custom_command(TARGET demo POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:demo>/assets
    COMMENT "Copying demo assets"
)

find_program(GLSLC glslc HINTS $ENV{VULKAN_SDK}/bin REQUIRED)

file(GLOB_RECURSE SHADER_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/*.vert
    ${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/*.frag
    ${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/*.comp
)

set(SHADER_OUTPUTS "")
foreach(SHADER ${SHADER_SOURCES})
    get_filename_component(SHADER_NAME ${SHADER} NAME)
    set(SPIRV_OUT ${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/${SHADER_NAME}.spv)
    add_custom_command(
        OUTPUT  ${SPIRV_OUT}
        COMMAND ${GLSLC} ${SHADER} -o ${SPIRV_OUT}
        DEPENDS ${SHADER}
        COMMENT "Compiling shader ${SHADER_NAME}"
    )
    list(APPEND SHADER_OUTPUTS ${SPIRV_OUT})
endforeach()

add_custom_target(update_shaders DEPENDS ${SHADER_OUTPUTS})

add_dependencies(demo update_shaders)