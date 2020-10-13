cmake_minimum_required(VERSION 3.2)

project(modern_crypto)

set (CMAKE_CXX_STANDARD 17)
SET("OpenCV_DIR" "/usr/local/Cellar/opencv/4.4.0_2")
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(modern_crypto demo.cpp DES.cpp AES.cpp crypto.cpp)
target_link_libraries(modern_crypto  ${OpenCV_LIBS} )
