cmake_minimum_required(VERSION 3.5)
project(turtle_control)

set(CMAKE_CXX_STANDARD 17)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(turtlesim REQUIRED)

add_executable(circle_driver src/circle_driver.cpp)
ament_target_dependencies(circle_driver rclcpp geometry_msgs turtlesim)

add_executable(pose_listener src/pose_listener.cpp)
ament_target_dependencies(pose_listener rclcpp turtlesim)

add_executable(go_to_goal src/go_to_goal.cpp)
ament_target_dependencies(go_to_goal rclcpp geometry_msgs turtlesim)

install(TARGETS
  circle_driver
  pose_listener
  go_to_goal
  DESTINATION lib/${PROJECT_NAME})

ament_package()