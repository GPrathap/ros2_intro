cmake_minimum_required(VERSION 3.5)
project(hello_world)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(friend_msgs REQUIRED)

set(dependencies
    rclcpp
    std_msgs
    friend_msgs
)

add_executable(publisher_node src/friend_hello_pub_todo.cpp)
ament_target_dependencies(publisher_node ${dependencies})

add_executable(publisher_class_node src/friend_hello_pub_class_todo.cpp)
ament_target_dependencies(publisher_class_node ${dependencies})

add_executable(subscriber_node src/friend_hello_sub_todo.cpp)
ament_target_dependencies(subscriber_node ${dependencies})

# add_executable(executor_nodes src/executor_nodes_todo.cpp)
# ament_target_dependencies(executor_nodes ${dependencies})

add_executable(param_reader_user_info src/set_name_and_id_todo.cpp)
ament_target_dependencies(param_reader_user_info ${dependencies})

add_executable(service_client src/friend_service_client.cpp)
ament_target_dependencies(service_client ${dependencies})

add_executable(service_server src/friend_service_server.cpp)
ament_target_dependencies(service_server ${dependencies})

install(TARGETS
  publisher_node
  # publisher_class_node 
  subscriber_node 
  # executor_nodes
  service_server
  # service_client
  param_reader_user_info 
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY launch config DESTINATION share/${PROJECT_NAME})
install(PROGRAMS scripts/hello_pub_todo.py scripts/hello_sub_todo.py DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_export_dependencies(${dependencies})
ament_package()
