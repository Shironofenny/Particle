# CMake project file for W4160 Computer Graphics
# Changxi Zheng (cxz@cs.columbia.edu)
# ===============================================
# Modified by Yihan Zhang
project(PARTICLE)

cmake_minimum_required(VERSION 2.6.2 FATAL_ERROR)

option(BUILD_DEBUG "Turn on the debug mode" OFF)

# ===================================================================
## Compiler
# set compiler flags for debug/release
if ( BUILD_DEBUG )
    add_definitions(-DDEBUG)
    set(CMAKE_BUILD_TYPE Debug)
else ()
    add_definitions(-Wno-deprecated)
    set(CMAKE_BUILD_TYPE Release)
endif ()

# set output executable path
set (EXECUTABLE_OUTPUT_PATH ../bin)

# add compiler flags
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

# add header files and source files (as there are some file I don't want to compile, I did not use recursive mode)
file (GLOB PARTICLE_HEADERS "./src/*.h" "./src/GameEngine/*.h" "./src/GameEngine/Utilities/*.h" "./src/GameEngine/Interaction/*.h" "./src/GameEngine/PhysicsEngine/*.h" "./src/GameEngine/ParticleSystem/*.h")
file (GLOB PARTICLE_SOURCES "./src/*.cpp" "./src/GameEngine/*.cpp" "./src/GameEngine/Utilities/*.cpp" "./src/GameEngine/Interaction/*.cpp" "./src/GameEngine/PhysicsEngine/*.cpp" "./src/GameEngine/ParticleSystem/*.cpp")

# package for opengl and glut
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(PNG REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/lib)

add_executable(particle ${PARTICLE_SOURCES})
target_link_libraries(particle ${GLUT_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${PNG_LIBRARIES})

file (COPY "./data/config.xml" DESTINATION ../bin/data)
file (COPY "./data/particle.xml" DESTINATION ../bin/data)
file (COPY "./data/texture/smoke.png" DESTINATION ../bin/data/texture)
