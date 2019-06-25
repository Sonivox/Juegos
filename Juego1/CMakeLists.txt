cmake_minimum_required(VERSION 3.14)
project(Juego1)

set(CMAKE_CXX_STANDARD 14)

# adding GLUT library
find_package(GLUT REQUIRED) # searching GLUT package
include_directories(${GLUT_INCLUDE_DIRS}) # add GLUT directories
link_directories(${GLUT_LIBRARY_DIRS}) # link GLUT directories
add_definitions(${GLUT_DEFINITIONS}) #A adding definitions


# adding OpenGL library
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

# adding OpenGL library
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
link_directories(${GLEW_LIBRARY_DIRS})
add_definitions(${GLEW_DEFINITIONS})

#######################################################
# INCLUYENDO LIBRERIA SOIL
#########################################################
link_directories(/usr/lib)
include_directories(/usr/include/)

include_directories(${GLFW_INCLUDE_DIRS})
include_directories(${GLEW_INCLUDE_DIRS})
add_definitions(-DGLEW_STATIC)
include_directories(${GLM_INCLUDE_DIRS})
include_directories(/usr/include/SOIL)
link_directories(/usr/lib/SOIL)

#######################################################
# INCLUYENDO LIBRERIA LSD
#########################################################
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(Juego1 main.cpp)

target_link_libraries(Juego1 ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLEW_LIBRARY} SOIL)