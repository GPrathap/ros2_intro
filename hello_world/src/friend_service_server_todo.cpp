#include <rclcpp/rclcpp.hpp>
// TODO import friend_info_service header 
#include <friend_msgs/srv/friend_info_service.hpp>
#include <memory>

// https://docs.ros.org/en/foxy/Tutorials/Beginner-Client-Libraries/Writing-A-Simple-Cpp-Service-And-Client.html

void add(const std::shared_ptr<friend_msgs::srv::FriendInfoService::Request> request,
          std::shared_ptr<friend_msgs::srv::FriendInfoService::Response>   response)
{
  response->heartbeat = request->value; 
}

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("service_server");

  rclcpp::Service<friend_msgs::srv::FriendInfoService>::SharedPtr service =
    node->create_service<friend_msgs::srv::FriendInfoService>("set_heartbeat", &add);


  // TODO Create a service with the name "set_heartbeat" and register a callback that should have two arguments:
  // request(std::shared_ptr<friend_msgs::srv::FriendInfoService::Request>) and response
  // (std::shared_ptr<friend_msgs::srv::FriendInfoService::Response>).
  // Inside the callback, print the request value and assign the response value, i.e., heartbeat, as the request value 
  
  rclcpp::spin(node);
  rclcpp::shutdown();

  return 0;
}
