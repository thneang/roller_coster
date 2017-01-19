cmake_minimum_required(VERSION 2.8)

project(roller_coster)

add_definitions(-std=c++11 -Wall )

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)

find_package(SDL REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(assimp REQUIRED)

include_directories(${SDL_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} glimac/include third-party/include ${ASSIMP_INCLUDE_DIRS} include)

set(ALL_LIBRARIES glimac ${SDL_LIBRARY} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY} ${ASSIMP_LIBRARIES})
file(GLOB_RECURSE SHADERS_FILES shaders/*)

file(GLOB SRC_DIRECTORIES "src/*")

add_subdirectory(glimac)

add_executable(roller_coster main.cpp ${SRC_DIRECTORIES} ${SHADERS_FILES})
target_link_libraries(roller_coster ${ALL_LIBRARIES})

# Copy files in build folder
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/textures DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
#configure_file(${CMAKE_CURRENT_SOURCE_DIR}/assets/textures/* ${CMAKE_CURRENT_BINARY_DIR}/assets/textures/* COPYONLY)
#configure_file(${CMAKE_CURRENT_SOURCE_DIR}/shaders/* ${CMAKE_CURRENT_BINARY_DIR}/shaders/* COPYONLY)