cmake_minimum_required(VERSION 3.28)
project(homeaudiolib)

set(CMAKE_CXX_STANDARD 17)

# Find libsndfile
find_package(SndFile REQUIRED)

# Include libsndfile headers
include_directories(${LIBSNDFILE_INCLUDE_DIRS})

# homeaudiolib
add_library(homeaudiolib STATIC library.cpp
        include/HAAudioBuffer.h
        src/AudioBuffer.cpp
        include/HAAudioIO.h
        src/AudioIO.cpp)


# Link libsndfile
target_link_libraries(homeaudiolib ${LIBSNDFILE_LIBRARIES})
