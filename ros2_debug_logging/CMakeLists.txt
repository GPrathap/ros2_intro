cmake_minimum_required(VERSION 3.8)
project(ros2_debug_logging)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rcutils REQUIRED)

set(dependencies
    rclcpp
    rcutils
)
include_directories(include)

add_executable(logging_basic src/logging_basic_todo.cpp)
ament_target_dependencies(logging_basic ${dependencies})


add_executable(astrobot_logger src/astrobot_node.cpp src/helpers.cpp)
ament_target_dependencies(astrobot_logger ${dependencies})

install(TARGETS
  logging_basic 
  astrobot_logger
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY launch DESTINATION share/${PROJECT_NAME})

ament_export_include_directories(include)
ament_export_dependencies(${dependencies})

ament_package()

