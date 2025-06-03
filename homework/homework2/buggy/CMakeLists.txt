cmake_minimum_required(VERSION 3.5)
project(buggy)


find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)


set(dependencies
    rclcpp
)

add_executable(sub src/sub.cpp)
ament_target_dependencies(sub ${dependencies})

install(TARGETS
  sub
  pub 
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY launch DESTINATION share/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_export_dependencies(${dependencies})
ament_package()