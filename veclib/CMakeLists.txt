cmake_minimum_required(VERSION 2.8)

project( veclib )
# The version number.
set (veclib_VERSION_MAJOR 1)
set (veclib_VERSION_MINOR 0)

#set this variable to specify a common place where CMake should put all libraries (instead of CMAKE_CURRENT_BINARY_DIR)
#set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

#Config output dir of compiled libraries lib folder to be used by infant.
set (youroutputdirectory ../lib)
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${youroutputdirectory} )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${youroutputdirectory} )
# Second, for multi-config builds (e.g. msvc) 
foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${youroutputdirectory} )
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${youroutputdirectory} )
    set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${youroutputdirectory} )
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )

#static \ shared lib
option(BUILD_VLIB_STATIC "Build veclib as shared library." ON)

set(veclibBuildType SHARED)
if (BUILD_VLIB_STATIC)
	set(veclibBuildType STATIC)
endif (BUILD_VLIB_STATIC)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/include veclibHeaders)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src veclibSources)


add_library( veclib ${veclibBuildType} ${veclibSources}  ${veclibHeaders} )




#set(CMAKE_BUILD_TYPE Release) ?
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
#add_library(veclib SHARED src/test.cpp)
#install (TARGETS MathFunctions DESTINATION bin)
#install (FILES MathFunctions.h DESTINATION include)

