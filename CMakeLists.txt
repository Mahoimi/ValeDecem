# Ask the user to have a minimum version of cmake, if not the project won't compile
cmake_minimum_required(VERSION 2.6)

# Name of the project
project(ValeDecem)

# Build cmake in the following directories
add_subdirectory(lib/assimp)
add_subdirectory(lib/sfml)
add_subdirectory(lib/anttweakbar)

add_definitions(-DGLEW_STATIC=1)
include_directories(lib/glew/include)
add_subdirectory(lib/glew)

find_package(OpenGL REQUIRED)

# Add all the files in src/ and include/ in a variable "source_files"
FILE(GLOB_RECURSE
    source_files
    ./src/*.cpp ./include/*.h ./shaders/*.glsl
)

#Set the default output directory
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# Add debug flags
SET(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build, options are: Debug Release." FORCE)
SET(CMAKE_CXX_COMPILER "g++")
SET(CMAKE_C_COMPILER "gcc")
SET(CMAKE_CXX_FLAGS "-Wall -fPIC -ffast-math -fvisibility-inlines-hidden -fvisibility=hidden ${SSE_FLAGS} -std=c++0x")
SET(CMAKE_CXX_FLAGS_DEBUG "-DDEBUG -g -ggdb -O0 -ftree-ter")
SET(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -g -O2")
SET(CMAKE_EXE_LINKER_FLAGS "")

# Make shortcuts to the following directories
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/lib/glm/)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/lib/assimp/include)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/lib/anttweakbar/include)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/lib/sfml/include)

# Compile the project with the "source_files" variable under the name "NbodySim"
add_executable(
        ValeDecem
        ${source_files}
)

target_link_libraries(ValeDecem sfml-window sfml-graphics sfml-audio AntTweakBar glew assimp ${OPENGL_LIBRARIES})
