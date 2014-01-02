cmake_minimum_required(VERSION 2.8)

project( sqlite3 )
# The version number.
set (veclib_VERSION_MAJOR 3)
set (veclib_VERSION_MINOR 8)

#set this variable to specify a common place where CMake should put all libraries (instead of CMAKE_CURRENT_BINARY_DIR)
#set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

#Config output dir of compiled libraries lib folder to be used by infant.
set (SQLiteOut ../lib)
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${SQLiteOut} )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${SQLiteOut} )
# Second, for multi-config builds (e.g. msvc) 
foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${SQLiteOut} )
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${SQLiteOut} )
    set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${SQLiteOut} )
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )

set(veclibBuildType STATIC)


include_directories(${CMAKE_CURRENT_SOURCE_DIR})
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SQLiteSources)

add_library( sqlite3 ${SQLiteSources})