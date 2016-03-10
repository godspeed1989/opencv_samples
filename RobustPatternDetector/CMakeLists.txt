cmake_minimum_required(VERSION 2.6)
project(RobustPatternDetector)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIR})

link_directories(${OpenCV_LIBRARY_DIR})

include_directories(./src)
add_subdirectory(src)
