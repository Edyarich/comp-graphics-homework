cmake_minimum_required(VERSION 3.8)
project(opengl_homework)

find_package(OpenGL REQUIRED)


if( CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR )
    message( FATAL_ERROR "Please select another Build Directory ! (and give it a clever name, like bin_Visual2012_64bits/)" )
endif()
if( CMAKE_SOURCE_DIR MATCHES " " )
    message( "Your Source Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()
if( CMAKE_BINARY_DIR MATCHES " " )
    message( "Your Build Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()

# Compile external dependencies
add_subdirectory(external)

# On Visual 2005 and above, this module can set the debug working directory
cmake_policy(SET CMP0026 OLD)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/external/rpavlik-cmake-modules-fe2273")
include(CreateLaunchers)
include(MSVCMultipleProcessCompile) # /MP

if(INCLUDE_DISTRIB)
    add_subdirectory(distrib)
endif(INCLUDE_DISTRIB)

include_directories(
        external/AntTweakBar-1.16/include/
        external/glfw-3.1.2/include/
        external/glm-0.9.7.1/
        external/glew-1.13.0/include/
        external/assimp-3.0.1270/include/
        external/bullet-2.81-rev2613/src/ .
)

set(ALL_LIBS
        ${OPENGL_LIBRARY}
        glfw
        GLEW_1130
        )

add_definitions(
        -DTW_STATIC
        -DTW_NO_LIB_PRAGMA
        -DTW_NO_DIRECT3D
        -DGLEW_STATIC
        -D_CRT_SECURE_NO_WARNINGS
)

# Crossed_triangles
add_executable(crossed_triangles
        crossed_triangles/crossed_triangles.cpp
        common/shader.cpp
        common/shader.hpp
        common/texture.cpp
        common/texture.hpp

        crossed_triangles/SimpleVertexShader.vertexshader
        crossed_triangles/SimpleFragmentShader.fragmentshader
        )
target_link_libraries(crossed_triangles
        ${ALL_LIBS}
        )
# Xcode and Visual working directories
set_target_properties(crossed_triangles PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/crossed_triangles/")
create_target_launcher(crossed_triangles WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/crossed_triangles/")


# Cylinder
add_executable(cylinder
        cylinder/cylinder.cpp
        common/shader.cpp
        common/shader.hpp
        common/texture.cpp
        common/texture.hpp

        cylinder/SimpleVertexShader.vertexshader
        cylinder/SimpleFragmentShader.fragmentshader
        )
target_link_libraries(cylinder
        ${ALL_LIBS}
        )
# Xcode and Visual working directories
set_target_properties(cylinder PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cylinder/")
create_target_launcher(cylinder WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/cylinder/")


# Animation_film
add_executable(animation_film
        animation_film/animation_film.cpp
        common/shader.cpp
        common/shader.hpp
        common/texture.cpp
        common/texture.hpp

        animation_film/SimpleVertexShader.vertexshader
        animation_film/SimpleFragmentShader.fragmentshader
        )
target_link_libraries(animation_film
        ${ALL_LIBS}
        )
# Xcode and Visual working directories
set_target_properties(animation_film PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/animation_film/")
create_target_launcher(animation_film WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/animation_film/")


SOURCE_GROUP(common REGULAR_EXPRESSION ".*/common/.*" )
SOURCE_GROUP(shaders REGULAR_EXPRESSION ".*/.*shader$" )


if (NOT ${CMAKE_GENERATOR} MATCHES "Xcode" )
add_custom_command(
        TARGET crossed_triangles POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/crossed_triangles${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/crossed_triangles/"
)
add_custom_command(
        TARGET cylinder POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/cylinder${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/cylinder/"
)
add_custom_command(
        TARGET animation_film POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/animation_film${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/animation_film/"
)

elseif (${CMAKE_GENERATOR} MATCHES "Xcode" )

endif (NOT ${CMAKE_GENERATOR} MATCHES "Xcode" )


