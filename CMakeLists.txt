cmake_minimum_required(VERSION 2.8)

project( Infant )

# add veclib cmake project
add_subdirectory (veclib)
add_subdirectory (sqlite)

set(LUA52_DIR "NOT-DEFINED" CACHE PATH "docstring")
# Load openCV and solve problem with include import on windows
find_package( OpenCV REQUIRED )
if (WIN32)
	set(OPENCV_INCLUDE_DIR2 "NOT-DEFINED" CACHE PATH "docstring")
endif()
# Load SQLite
option(DEFAULT_SQLITE3 "Use provided SQLITE amalgamation 3.8.4" ON)
if(DEFAULT_SQLITE3)
	message("Setting default SQLite amalgamation 3.8.4")
	include_directories(${CMAKE_CURRENT_SOURCE_DIR}/sqlite)	
	#aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/sqlite SQLiteSources)
	#add_subdirectory (sqlite)
else()
	message("Setting system SQLite version")
	find_package( SQLite REQUIRED )
endif()

# load lua.
include_directories(${LUA52_DIR}/include)
link_directories(${LUA52_DIR})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/veclib/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

if (WIN32)
	message("Setting custom OpenCV include directory")
	include_directories(${OpenCV_INCLUDE_DIR2})
endif()

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/include InfantHeaders)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src InfantSources)


add_executable( Infant ${InfantHeaders} ${InfantSources} Infant.cpp)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/veclib)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/sqlite)
link_directories(${LUA52_DIR}) 

target_link_libraries( Infant ${OpenCV_LIBS} veclib sqlite3 lua52)