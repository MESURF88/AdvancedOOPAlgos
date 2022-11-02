cmake_minimum_required(VERSION 3.16.0)

set(ProjName advanced)

project(${ProjName} VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/target)
message("${CMAKE_BINARY_DIR}")

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

# include files
set(includes
Parent.hpp
Child.hpp
BrainChild.hpp
Animal.hpp
)

# source files
set(source
Parent.cpp
Child.cpp
BrainChild.cpp
Animal.cpp
main.cpp
)

add_executable(${ProjName} ${includes} ${source})

if (CMAKE_GENERATOR MATCHES "NMake Makefiles")
set_target_properties( ${ProjName}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/nmake/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/nmake/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/nmake/bin"
)
else()
set_target_properties( ${ProjName}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
endif()
