cmake_minimum_required(VERSION 3.5)

project(ros2_composition)

set(CMAKE_CXX_STANDARD 17)


if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(friend_msgs REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(rcutils REQUIRED)
find_package(std_msgs REQUIRED)

include_directories(include)

set(dependencies
    rclcpp
    std_msgs
    friend_msgs
    rclcpp_components
    rcutils
)

set(node_plugins "")

add_library(hello_world_pub_component SHARED src/hello_world_pub_component.cpp)
target_compile_definitions(hello_world_pub_component PRIVATE "COMPOSITION_BUILDING_DLL")
ament_target_dependencies(hello_world_pub_component ${dependencies})
rclcpp_components_register_nodes(hello_world_pub_component "composition::SenderNode")
set(node_plugins "${node_plugins}composition::SenderNode;$<TARGET_FILE:hello_world_pub_component>\n")

add_library(hello_world_sub_component SHARED src/hello_world_sub_component.cpp)
target_compile_definitions(hello_world_sub_component PRIVATE "COMPOSITION_BUILDING_DLL")
ament_target_dependencies(hello_world_sub_component ${dependencies})
rclcpp_components_register_nodes(hello_world_sub_component "composition::ReceiverNode")
set(node_plugins "${node_plugins}composition::ReceiverNode;$<TARGET_FILE:hello_world_sub_component>\n")

add_library(hello_world_service_server SHARED src/hello_world_service_server.cpp)
target_compile_definitions(hello_world_service_server PRIVATE "COMPOSITION_BUILDING_DLL")
ament_target_dependencies(hello_world_service_server ${dependencies})
rclcpp_components_register_nodes(hello_world_service_server "composition::Server")
set(node_plugins "${node_plugins}composition::Server;$<TARGET_FILE:hello_world_service_server>\n")

add_library(hello_world_service_client SHARED src/hello_world_service_client.cpp)
target_compile_definitions(hello_world_service_client PRIVATE "COMPOSITION_BUILDING_DLL")
ament_target_dependencies(hello_world_service_client ${dependencies})
rclcpp_components_register_nodes(hello_world_service_client "composition::Client")
set(node_plugins "${node_plugins}composition::Client;$<TARGET_FILE:hello_world_service_client>\n")


ament_environment_hooks("${ament_cmake_package_templates_ENVIRONMENT_HOOK_LIBRARY_PATH}")


add_executable(manual_composition src/manual_composition.cpp)
target_link_libraries(manual_composition
  hello_world_pub_component
  hello_world_sub_component
  hello_world_service_server
  hello_world_service_client)

ament_target_dependencies(manual_composition "rclcpp")

install(TARGETS
  hello_world_pub_component
  hello_world_sub_component
  hello_world_service_server
  hello_world_service_client
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin)

install(TARGETS manual_composition DESTINATION lib/${PROJECT_NAME})

install(DIRECTORY launch DESTINATION share/${PROJECT_NAME})

ament_package()
