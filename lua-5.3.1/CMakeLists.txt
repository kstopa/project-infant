# Krzysztof Stopa, 2015

cmake_minimum_required(VERSION 2.8)

project( lua )
# The version number.
set (lua_VERSION_MAJOR 5)
set (lua_VERSION_MINOR 3)

#Config output dir of compiled libraries lib folder to be used by infant.
set (OUTPUTDIR ${CMAKE_CURRENT_SOURCE_DIR})
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUTDIR}/lib )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUTDIR}/bin )

#static \ shared lib
option(BUILD_VLIB_STATIC "Build veclib as shared library." ON)

set(LUA_BUILD_TYPE SHARED)
if (BUILD_VLIB_STATIC)
	set(veclibBuildType STATIC)
endif (BUILD_VLIB_STATIC)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src LUA_SOURCES)

# Lua library
add_library( lua ${LUA_BUILD_TYPE} ${LUA_SOURCES})
# Lua compiler
add_executable( luac luac.c)
target_link_libraries( luac lua)
