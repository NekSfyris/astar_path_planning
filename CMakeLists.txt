cmake_minimum_required(VERSION 3.2)

project(path_planning)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)

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

# Include the 'include' directory for header files
target_include_directories(${PROJECT_NAME} PRIVATE include)

# Find and link SDL2 (adjust if needed)
find_package(SDL2 REQUIRED)
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES})

# You can add other dependencies here if necessary

# Set the output directory to the project root
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

# If you need additional configuration or settings, add them here
