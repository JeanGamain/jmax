cmake_minimum_required(VERSION 3.1)

project(jmax)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  # Update if necessary
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(EXECUTABLE_OUTPUT_PATH ../bin/)

set(jmax
	jmax/main.cpp
	jmax/load.cpp
	jmax/loadOffFile.cpp
	jmax/loadObjFile.cpp
	jmax/loadMtlFile.cpp
	jmax/bind.cpp
	jmax/handler.cpp
	jmax/engine.cpp
	jmax/camera.cpp
	jmax/model.cpp
	jmax/material.cpp
	)

set(jmax_includes_directories
	jmax/
	)

foreach(DIRECTORY ${jmax_includes_directories}) 
    # Get the directory of the source file
    FILE(GLOB tmp RELATIVE "${CMAKE_SOURCE_DIR}/" ${DIRECTORY}/*.hpp)
    set(jmax_includes ${server_includes} ${tmp})
endforeach()

add_executable(jmax ${jmax} ${jmax_includes})

set_target_properties(jmax PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${EXECUTABLE_OUTPUT_PATH}")
set_target_properties(jmax PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${EXECUTABLE_OUTPUT_PATH}")

target_compile_features(jmax PRIVATE cxx_range_for)
target_include_directories(jmax PRIVATE ${server_includes_directories})


if (APPLE)
  set(CMAKE_MACOSX_RPATH ON)
  set(CMAKE_SKIP_BUILD_RPATH FALSE)
  set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
  set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
  set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
  list(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/lib" isSystemDir)
  if("${isSystemDir}" STREQUAL "-1")
    set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
  endif()
endif(APPLE)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/" ${CMAKE_MODULE_PATH})

find_package(OpenGL REQUIRED)
if(OPENGL_FOUND)
  include_directories(${OPENGL_INCLUDE_DIR})
  target_link_libraries(jmax ${OPENGL_LIBRARIES})
endif()

find_package(GLFW REQUIRED)
if(GLFW_FOUND)
  include_directories(${GLFW_INCLUDE_DIR})
  target_link_libraries(jmax ${GLFW_LIBRARIES})
endif()

find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
    target_link_libraries(jmax ${GLEW_LIBRARIES})
endif()

find_package(SOIL REQUIRED)
if (SOIL_FOUND)
    include_directories(${SOIL_INCLUDE_DIRS})
    target_link_libraries(jmax ${SOIL_LIBRARIES})
endif()

FILE(GLOB_RECURSE all_files *.*pp)

foreach(FILE ${all_files}) 
    # Get the directory of the source file
    get_filename_component(PARENT_DIR "${FILE}" DIRECTORY)

    # Remove common directory prefix to make the group
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" GROUP "${PARENT_DIR}")

    # Make sure we are using windows slashes
    string(REPLACE "/" "\\" GROUP "${GROUP}")

    # Group into "Source Files" and "Header Files"
    if ("${FILE}" MATCHES ".*\\.cpp")
       set(GROUP "Source Files${GROUP}")
    elseif("${FILE}" MATCHES ".*\\.hpp")
       set(GROUP "Header Files${GROUP}")
    endif()

    source_group("${GROUP}" FILES "${FILE}")
endforeach()
