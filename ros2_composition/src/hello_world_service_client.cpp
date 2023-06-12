#include "composition/hello_world_service_client.hpp"

using namespace std::chrono_literals;

namespace composition
{

Client::Client(const rclcpp::NodeOptions & options)
: Node("service_client", options)
{
  client_ = create_client<friend_msgs::srv::FriendInfoService>("set_heartbeat");
  timer_ = create_wall_timer(2s, std::bind(&Client::on_timer, this));
}

void Client::on_timer()
{
  if (!client_->wait_for_service(1s)) {
    if (!rclcpp::ok()) {
      RCLCPP_ERROR(
        this->get_logger(),
        "Interrupted while waiting for the service. Exiting.");
      return;
    }
    RCLCPP_INFO(this->get_logger(), "Service not available after waiting");
    return;
  }

  auto request = std::make_shared<friend_msgs::srv::FriendInfoService::Request>();
  request->id = 5678;
  request->value = 345;

  using ServiceResponseFuture =
    rclcpp::Client<friend_msgs::srv::FriendInfoService>::SharedFuture;
  auto response_received_callback = [this](ServiceResponseFuture future) {
      RCLCPP_INFO(this->get_logger(), "Heartbeat: %d ", future.get()->heartbeat);
    };
  auto future_result = client_->async_send_request(request, response_received_callback);
}

}  // namespace composition

#include "rclcpp_components/register_node_macro.hpp"

RCLCPP_COMPONENTS_REGISTER_NODE(composition::Client)
