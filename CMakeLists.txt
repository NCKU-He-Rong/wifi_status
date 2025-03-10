cmake_minimum_required(VERSION 3.0.2)
project(wifi_status)

find_package(catkin REQUIRED COMPONENTS
      roscpp
)

catkin_package()

include_directories(${catkin_INCLUDE_DIRS})

add_executable(wifi_monitor src/main.cpp)
target_link_libraries(wifi_monitor ${catkin_LIBRARIES})
