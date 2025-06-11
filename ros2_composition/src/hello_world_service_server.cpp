#include "composition/hello_world_service_server.hpp"


namespace composition
{

Server::Server(const rclcpp::NodeOptions & options): Node("service_server", options)
{
  auto set_heartbeat =
    [this](std::shared_ptr<friend_msgs::srv::FriendInfoService::Request> req,
        std::shared_ptr<friend_msgs::srv::FriendInfoService::Response> res) -> void
    {
      res->heartbeat = req->value;
      RCLCPP_INFO_STREAM(this->get_logger(), "Incoming request: " << req->value);
      std::flush(std::cout);
    };

  service = create_service<friend_msgs::srv::FriendInfoService>("set_heartbeat", set_heartbeat);
}

}  

#include "rclcpp_components/register_node_macro.hpp"

RCLCPP_COMPONENTS_REGISTER_NODE(composition::Server)
