#include "composition/hello_world_pub_component.hpp"

#include <chrono>
#include <iostream>
#include <memory>
#include <utility>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

namespace composition
{

// Create a Talker "component" that subclasses the generic rclcpp::Node base class.
// Components get built into shared libraries and as such do not write their own main functions.
// The process using the component's shared library will instantiate the class as a ROS node.
SenderNode::SenderNode(const rclcpp::NodeOptions & options): Node("SenderNode", options), count_(0)
{
      pub_ = create_publisher<friend_msgs::msg::FriendInfo>("/r2d2_pose", 10);
      timer_ = create_wall_timer(500ms, std::bind(&SenderNode::timer_callback, this));
}

void SenderNode::timer_callback(){
      message_.id = 345;
      message_.name = "d2r2";
      RCLCPP_INFO(this->get_logger(), "Publishing: id '%d'", message_.id);
      std::flush(std::cout);
      pub_->publish(message_);
}

}  // namespace composition

#include "rclcpp_components/register_node_macro.hpp"

// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
RCLCPP_COMPONENTS_REGISTER_NODE(composition::SenderNode)
