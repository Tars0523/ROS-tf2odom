cmake_minimum_required(VERSION 2.8)
project(tf2odom)

find_package(catkin REQUIRED nav_msgs roscpp tf)

include_directories(${catkin_INCLUDE_DIRS})

catkin_package()

add_executable(tf2odom src/tf2odom.cpp)
target_link_libraries(tf2odom ${catkin_LIBRARIES})
