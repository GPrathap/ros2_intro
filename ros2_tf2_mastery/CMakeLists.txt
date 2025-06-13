cmake_minimum_required(VERSION 3.5)
project(ros2_tf2_mastery)


find_package(rclcpp REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)

set(dependencies
    rclcpp
    tf2
    tf2_ros
    geometry_msgs
    tf2_geometry_msgs
)

add_executable(static_transform_broadcaster src/static_transform_broadcaster.cpp)
ament_target_dependencies(static_transform_broadcaster ${dependencies})

add_executable(dynamic_transform_broadcaster src/dynamic_transform_broadcaster.cpp)
ament_target_dependencies(dynamic_transform_broadcaster ${dependencies})

add_executable(transform_listener src/transform_listener_node.cpp)
ament_target_dependencies(transform_listener ${dependencies})

install(TARGETS
  static_transform_broadcaster
  dynamic_transform_broadcaster
  transform_listener
  DESTINATION lib/${PROJECT_NAME})

install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME})

ament_package()
