cmake_minimum_required(VERSION 3.5)
project(homework1)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(std_srvs REQUIRED)
find_package(geometry_msgs REQUIRED)

set(CMAKE_CXX_STANDARD 17)

set(dependencies
    rclcpp
    std_msgs
    std_srvs
    geometry_msgs 
)

add_executable(commander_node src/commander_node.cpp)
ament_target_dependencies(commander_node ${dependencies})

install(TARGETS
  commander_node
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

ament_export_include_directories(include)
ament_export_dependencies(${dependencies})

ament_package()

