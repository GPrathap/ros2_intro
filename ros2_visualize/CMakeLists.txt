cmake_minimum_required(VERSION 3.5)
project(ros2_visualize)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(visualization_msgs REQUIRED)
find_package(diagnostic_updater REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)
find_package(image_transport REQUIRED)
find_package(pcl_conversions REQUIRED)
find_package(interactive_markers REQUIRED)
find_package(friend_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(OpenCV)
# sudo apt-get -y install pcl-tools
find_package(Boost COMPONENTS system REQUIRED)
find_package(PCL COMPONENTS common REQUIRED)

set(CMAKE_CXX_STANDARD 17)

set(dependencies
  rclcpp
  std_msgs
  geometry_msgs 
  visualization_msgs 
  diagnostic_updater 
  cv_bridge  
  image_transport 
  pcl_conversions 
  interactive_markers 
  friend_msgs
  sensor_msgs
  tf2
  tf2_ros
  tf2_geometry_msgs
  nav_msgs
)


include_directories(${OpenCV_INCLUDE_DIRS} ${PCL_INCLUDE_DIRS})

add_executable(joy_hagen_sub src/joy_hagen_sub_todo.cpp)
ament_target_dependencies(joy_hagen_sub ${dependencies})

add_executable(joy_hagen_pub src/joy_hagen_pub_todo.cpp)
ament_target_dependencies(joy_hagen_pub ${dependencies})

add_executable(joy_hagen_point_cloud src/joy_hagen_point_cloud.cpp)
ament_target_dependencies(joy_hagen_point_cloud ${dependencies} )
target_link_libraries(joy_hagen_point_cloud ${PCL_LIBRARIES} ${Boost_SYSTEM_LIBRARY})

add_executable(joy_hagen_marker_array src/joy_hagen_marker_array.cpp)
ament_target_dependencies(joy_hagen_marker_array ${dependencies} )
target_link_libraries(joy_hagen_marker_array ${PCL_LIBRARIES} ${Boost_SYSTEM_LIBRARY})

add_executable(joy_hagen_camera src/joy_hagen_camera_todo.cpp)
ament_target_dependencies(joy_hagen_camera ${dependencies} )
target_link_libraries(joy_hagen_camera ${PCL_LIBRARIES} ${Boost_SYSTEM_LIBRARY} ${OpenCV_LIBRARIES})

add_executable(joy_hagen_basic_control src/joy_hagen_basic_control_todo.cpp)
ament_target_dependencies(joy_hagen_basic_control ${dependencies} )
target_link_libraries(joy_hagen_basic_control  ${Boost_SYSTEM_LIBRARY})

install(TARGETS 
  joy_hagen_sub 
  joy_hagen_marker_array
  joy_hagen_basic_control 
  joy_hagen_pub
  joy_hagen_camera
  joy_hagen_point_cloud 
  ARCHIVE DESTINATION lib 
  LIBRARY DESTINATION lib 
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY launch DESTINATION share/${PROJECT_NAME})

ament_export_include_directories(include)
ament_export_dependencies(${dependencies})
ament_package()
