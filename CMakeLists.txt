# CMakeLists.txt

cmake_minimum_required(VERSION 3.12)
project(ledis)

# Prompt the user for concurrent strategy
set(CONCURRENT_STRATEGY "POOLING" CACHE STRING "Choose the concurrent strategy (POOLING or THREADS)")

# Use the selected option to define a preprocessor macro
if(CONCURRENT_STRATEGY STREQUAL "POOLING")
    add_definitions(-DCONCURRENT_POOLING)
elseif(CONCURRENT_STRATEGY STREQUAL "THREADS")
    add_definitions(-DCONCURRENT_THREADS)
else()
    message(FATAL_ERROR "Invalid value for CONCURRENT_STRATEGY. Choose POOLING or THREADS.")
endif()

# Include directories
include_directories(include)

# Add source files
file(GLOB SOURCE_FILES "src/*.c")

# Create the executable
add_executable(ledis_server ${SOURCE_FILES})

# Link libraries if needed
# target_link_libraries(ledis_server some_library)

# Install executable
install(TARGETS ledis_server DESTINATION bin)