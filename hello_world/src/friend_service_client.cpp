#include <rclcpp/rclcpp.hpp>
#include <friend_msgs/srv/friend_info_service.hpp>
#include <memory>
#include <chrono>
#include <cstdlib>

using namespace std::chrono_literals;

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);

  // if (argc != 2)
  // {
  //   RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "usage: need id and value");
  //   return 1;
  // }

  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("service_client");

  rclcpp::Client<friend_msgs::srv::FriendInfoService>::SharedPtr client =
      node->create_client<friend_msgs::srv::FriendInfoService>("set_heartbeat");

 while(true){
    auto request = std::make_shared<friend_msgs::srv::FriendInfoService::Request>();
    request->id = 45678;
    request->value = 345;
    while (!client->wait_for_service(1s)){
      if(!rclcpp::ok()){
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted waiting for the service");
        return 0;
      }
      RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Service is not available yet, waiting...");
    }

    auto result = client->async_send_request(request);
    if(rclcpp::spin_until_future_complete(node, result) == rclcpp::FutureReturnCode::SUCCESS){
      RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Heartbeat: %d ", result.get()->heartbeat);
    }else{
      RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call the service server");
    }

 }
  
  rclcpp::shutdown();
  return 0;
  // TODO create a service client with the name get_friend_value
  // TODO Call the service and read the response and print the response.
  //  If the service is unavailable printer service is not available
}
