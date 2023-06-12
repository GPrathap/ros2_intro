#include <rclcpp/rclcpp.hpp>
#include <friend_msgs/srv/friend_info_service.hpp>
#include <memory>

bool setHeartBeat(std::shared_ptr<friend_msgs::srv::FriendInfoService::Request> req,
        std::shared_ptr<friend_msgs::srv::FriendInfoService::Response> res)
{
  res->heartbeat = req->value;
  return true;
}

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("service_server");

  rclcpp::Service<friend_msgs::srv::FriendInfoService>::SharedPtr service = 
    node->create_service<friend_msgs::srv::FriendInfoService>("set_heartbeat", &setHeartBeat);
  // TODO Create service and register a callback with two arguments; name the callback function as addition
  // Inside the callback, print request value and assign the response value, i.e., heartbeat, as the request value 
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Service server is ready");
  
  rclcpp::spin(node);
  rclcpp::shutdown();

  return 0;
}
