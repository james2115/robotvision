cmake_minimum_required(VERSION 3.0)
project(ball)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES src/main.cpp src/debug.cpp src/gearbox.cpp)

find_package(OpenCV REQUIRED)

include_directories("include" ${OpenCV_INCLUDE_DIRS})

add_executable(ball ${SOURCE_FILES})
target_link_libraries(ball ${OpenCV_LIBS})
