cmake_minimum_required(VERSION 2.6)
project(MiniLD45)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

set(BUILD_STATIC TRUE CACHE BOOL "TRUE to build static libraries, FALSE to build shared libraries (preferred)")
set(BUILD_GAME TRUE CACHE BOOL "TRUE to build the game, FALSE to not build it")

set(GLFWDIR "" CACHE PATH "Path to glfw dir")
set(GLM_ROOT_DIR "" CACHE PATH "Path to glm dir")
set(GLEWDIR "" CACHE PATH "Path to glew dir")
set(GLDIR "" CACHE PATH "Path to openGL dir")

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake-extras/")

set(GLFWDIR "${PROJECT_SOURCE_DIR}/dependencies/glfw")
set(GLM_ROOT_DIR "${PROJECT_SOURCE_DIR}/dependencies/glm")
set(GLEWDIR "${PROJECT_SOURCE_DIR}/dependencies/glew")

ADD_SUBDIRECTORY(Dependencies)
find_package(GL REQUIRED)

include_directories(SYSTEM ${PROJECT_SOURCE_DIR}/MiniLD45/src/ ${PROJECT_SOURCE_DIR}/Dependencies/glfw/include/ ${PROJECT_SOURCE_DIR}/Dependencies/glm/ ${gl_INCLUDE_DIRS})

add_subdirectory(${PROJECT_SOURCE_DIR}/MLD45)

install(DIRECTORY "${PROJECT_SOURCE_DIR}/MLD45/src/" DESTINATION include/MLD45 FILES_MATCHING PATTERN "*.h")
