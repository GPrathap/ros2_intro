#include "composition/hello_world_sub_component.hpp"

#include <iostream>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

namespace composition
{

ReceiverNode::ReceiverNode(const rclcpp::NodeOptions & options)
: Node("receiver_node", options)
{
  // Create a callback function for when messages are received.
  // Variations of this function also exist using, for example, UniquePtr for zero-copy transport.
  auto callback =
    [this](friend_msgs::msg::FriendInfo::ConstSharedPtr msg) -> void
    {
      RCLCPP_INFO(this->get_logger(), "Hello %d", msg->id);
      std::flush(std::cout);
    };

  subscriber_ = create_subscription<friend_msgs::msg::FriendInfo>("/r2d2_pose", 10, callback);
}

}  // namespace composition

#include "rclcpp_components/register_node_macro.hpp"

RCLCPP_COMPONENTS_REGISTER_NODE(composition::ReceiverNode)
