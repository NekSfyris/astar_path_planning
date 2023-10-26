cmake_minimum_required(VERSION 3.2)

project(path_planning)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH "/usr/share/cmake/Modules")

set(CMAKE_PREFIX_PATH "/usr")
set(ENV{PKG_CONFIG_PATH} "/usr/lib/pkgconfig:$ENV{PKG_CONFIG_PATH}")

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

# Source files
file(GLOB SOURCE_FILES
    src/*.cpp
)

# Header files
file(GLOB HEADER_FILES
    include/*.h
)

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE include ${SDL2_INCLUDE_DIRS}  ${SDL2_TTF_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES})


# Set the output directory to the project root
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})