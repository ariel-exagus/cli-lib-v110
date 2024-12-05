cmake_minimum_required(VERSION 3.1.3)

# Set name of project (as PROJECT_NAME)
project(cli-lib-v110)

# specify the C standard
set(CMAKE_C_STANDARD 99)
# Opcional: Requerir el estándar explícitamente sin permitir extensiones del compilador.
set(CMAKE_C_STANDARD_REQUIRED true)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# Add include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add all the sources files in src
file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.c)

# Add main.cpp file
set(SOURCES ${SOURCES} ${CMAKE_SOURCE_DIR}/main.c)

# Add the executables
add_executable(${PROJECT_NAME} ${SOURCES})

#In windows, use the next command to generate de MakeFile: cmake .. -G "MinGW Makefiles"