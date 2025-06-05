#include <rclcpp/rclcpp.hpp>
// TODO import friend_info_service header 
#include <friend_msgs/srv/friend_info_service.hpp>
#include <memory>
#include <chrono>
#include <cstdlib>

// https://docs.ros.org/en/foxy/Tutorials/Beginner-Client-Libraries/Writing-A-Simple-Cpp-Service-And-Client.html

using namespace std::chrono_literals;

// TODO create a service client with the name service_client
//     1). Call the service, i.e, set_heartbeat, that must be type of friend_msgs::srv::FriendInfoService
//     2). Set the id and value for the request, 
//     3). Check whether service is available or not 
//     4). If service is available send the request and print the response message  
//     5). If the service is unavailable print a warning message saying "service is not available"

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);

  if (argc != 2)
  {
    RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "usage: need id and value");
    return 1;
  }
  
  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("service_client");
  rclcpp::Client<friend_msgs::srv::FriendInfoService>::SharedPtr client =
    node->create_client<friend_msgs::srv::FriendInfoService>("set_heartbeat");

  
  while (true)
  {
    auto request = std::make_shared<friend_msgs::srv::FriendInfoService::Request>();
    request->id = 3456;
    request->value = 5657;
    while (!client->wait_for_service(1s)) {
      if (!rclcpp::ok()) {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting.");
        return 0;
      }
      RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
    }
    auto result = client->async_send_request(request);
    if(rclcpp::spin_until_future_complete(node, result) == rclcpp::FutureReturnCode::SUCCESS){
      RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Heartbeat %d ", result.get()->heartbeat);
    }else{
      RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call service set_heartbeat");
    }
  }

  rclcpp::shutdown();
  return 0;
}
