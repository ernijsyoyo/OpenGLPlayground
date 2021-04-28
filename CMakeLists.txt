#Project Setup
cmake_minimum_required(VERSION 3.0)

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS "-std=c++17")
project(openGLPlayground)
#enable_testing()

# Add sub directories
add_subdirectory(libs)

# Create a sources variable with a link to all cpp files to compile
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

set(INCL_FILES_DIR "${PROJECT_SOURCE_DIR}/include/")
set(GLFW_INCLUDE "${PROJECT_SOURCE_DIR}/libs/glfw/include")
set(GLAD_INCLUDE "${PROJECT_SOURCE_DIR}/libs/glad/include/glad")
set(KHR_INCLUDE "${PROJECT_SOURCE_DIR}/libs/glad/include/KHR")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

# Local include/ folder
include_directories(
      ${INCL_FILES_DIR}
      ${GLFW_INCLUDE}
      ${GLAD_INCLUDE}
      ${KHR_INCLUDE}
)

# Add an executable with the above sources
add_executable(openGLPlayground ${SOURCES} ${STBIMG})
target_link_libraries(openGLPlayground glfw ${GLFW_LIBRARIES} sub::libGlad)


# ---------- POST BUILD ---------------
# Copy all shaders next to the binary
# Delete old res directory in case CMake has any files cached and doesnt overwrite them
# https://stackoverflow.com/questions/13429656/how-to-copy-contents-of-a-directory-into-build-directory-after-make-with-cmake
add_custom_command(TARGET openGLPlayground POST_BUILD 
                  COMMAND ${CMAKE_COMMAND} -E remove_directory
                  "${CMAKE_SOURCE_DIR}/bin/res/" )

add_custom_command(TARGET openGLPlayground POST_BUILD 
                  COMMAND ${CMAKE_COMMAND} -E copy_directory 
                  "${CMAKE_SOURCE_DIR}/res/" 
                  "${CMAKE_SOURCE_DIR}/bin/res/")
