cmake_minimum_required(VERSION 3.10)

project(AtomSoup VERSION 1.0)
set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(FALSE)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")
SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -pg")
endif()

include_directories("inc")
set(SOURCES
	src/commons.cpp
	src/atom.cpp
	src/soup.cpp)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
add_library(Modules SHARED ${SOURCES})

add_executable(AtomSoup main.cpp)
target_compile_options(AtomSoup PRIVATE -Wall)
target_link_libraries(AtomSoup sfml-graphics sfml-audio Modules)
