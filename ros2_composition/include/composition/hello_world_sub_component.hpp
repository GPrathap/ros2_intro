#ifndef COMPOSITION__HELLO_FRIEND_SUB_COMPONENT_HPP_
#define COMPOSITION__HELLO_FRIEND_SUB_COMPONENT_HPP_

#include "composition/visibility_control.h"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include <friend_msgs/msg/friend_info.hpp>

namespace composition
{

class ReceiverNode : public rclcpp::Node
{
public:
  COMPOSITION_PUBLIC
  explicit ReceiverNode(const rclcpp::NodeOptions & options);

private:
  rclcpp::Subscription<friend_msgs::msg::FriendInfo>::SharedPtr subscriber_;
};

}  // namespace composition

#endif  // COMPOSITION__HELLO_FRIEND_SUB_COMPONENT_HPP_
