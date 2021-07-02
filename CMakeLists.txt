cmake_minimum_required(VERSION 3.16)
project("puffer-fish")

#BASICALLY REALEASE MODE
SET(CMAKE_CXX_FLAGS  "-m64 -Ofast -flto -march=native -funroll-loops")

#DEBUGMODE
#SET(CMAKE_CXX_FLAGS "-g -ggdb")
#SET(CMAKE_CXX_FLAGS "-g")

#PROFILERMODE
#SET(CMAKE_CXX_FLAGS "-g -pg")

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

include(FindPkgConfig)
find_library(SDL2 SDL2)
find_package(SDL2 REQUIRED)
find_library(SDL2_ttf SDL2_ttf)
find_library(SDL2_image SDL2_image)
find_package(SDL2_image REQUIRED)
find_package(Threads REQUIRED)
include_directories(vendor/glm/)
include_directories(vendor/yamc/include/)

#creating the executable of the engine test
include_directories(src/)
file(GLOB_RECURSE "puffer-fish" SRC src/*.cpp)
add_executable(puffer-fish ${puffer-fish})

target_link_libraries(puffer-fish LINK_PRIVATE "${SDL2}")
target_link_libraries(puffer-fish LINK_PRIVATE "${SDL2_ttf}")
target_link_libraries(puffer-fish LINK_PRIVATE "${SDL2_image}")
target_link_libraries(puffer-fish LINK_PRIVATE Threads::Threads)

add_definitions(-std=c++11)