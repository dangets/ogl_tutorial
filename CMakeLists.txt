cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "-Wall -std=c++11")

project(OGL_TUTORIAL)


set(OGL_TUTORIAL_INCLUDES)
set(OGL_TUTORIAL_LIBS)


# gl_core library ---
add_library(gl_core_3_3 STATIC gl_core_3_3.c)
list(APPEND OGL_TUTORIAL_LIBS gl_core_3_3)


# GLM ---------------
find_package(GLM 0.9)
set(GLM_INCLUDE_DIR "${GLM_INCLUDE_DIR}" CACHE PATH "GLM include directory")
if (NOT ${GLM_INCLUDE_DIR})
	find_path(GLM_INCLUDE_DIR glm/glm.hpp)
endif()

list(APPEND OGL_TUTORIAL_INCLUDES ${GLM_INCLUDE_DIR})


# GLFW --------------
find_package(glfw 3)
set(GLFW_INCLUDE_DIR "${GLFW_INCLUDE_DIR}" CACHE PATH "GLFW include directory")
if (NOT ${GLFW_INCLUDE_DIR})
	find_path(GLFW_INCLUDE_DIR GLFW/glfw3.h)
endif()

list(APPEND OGL_TUTORIAL_INCLUDES ${GLFW_INCLUDE_DIR})

set(GLFW_LIBRARY "${GLFW_LIBRARY}" CACHE FILEPATH "GLFW library")
if (NOT ${GLFW_LIBRARY})
	find_library(GLFW_LIBRARY glfw)
endif()

list(APPEND OGL_TUTORIAL_LIBS ${GLFW_LIBRARY})


if(UNIX)
	find_package(OpenGL REQUIRED)
	list(APPEND OGL_TUTORIAL_LIBS ${OPENGL_gl_LIBRARY})

	find_package(Threads REQUIRED)
	list(APPEND OGL_TUTORIAL_LIBS ${CMAKE_THREAD_LIBS_INIT})

	find_package(X11 REQUIRED)
	list(APPEND OGL_TUTORIAL_LIBS ${X11_Xrandr_LIB} ${X11_Xxf86vm_LIB} ${X11_Xi_LIB})

	find_library(RT_LIB rt)
	list(APPEND OGL_TUTORIAL_LIBS ${RT_LIB})
endif()


add_library(ogl_tutorial STATIC GLSLShader.cpp GLSLProgram.cpp TriangleModel.cpp)
list(APPEND OGL_TUTORIAL_LIBS ogl_tutorial)

include_directories(${OGL_TUTORIAL_INCLUDES})

add_executable(dump_gl_info dump_gl_info.cpp)
target_link_libraries(dump_gl_info ${OGL_TUTORIAL_LIBS})

add_executable(triangle_2d triangle_2d.cpp)
target_link_libraries(triangle_2d ${OGL_TUTORIAL_LIBS})

add_executable(triangle_2d_model triangle_2d_model.cpp)
target_link_libraries(triangle_2d_model ${OGL_TUTORIAL_LIBS})

