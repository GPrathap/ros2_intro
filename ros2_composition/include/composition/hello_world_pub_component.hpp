#ifndef COMPOSITION__HELLO_FRINED_PUB_COMPONENT_HPP_
#define COMPOSITION__HELLO_FRINED_PUB_COMPONENT_HPP_

#include "composition/visibility_control.h"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include <friend_msgs/msg/friend_info.hpp>

namespace composition
{

class SenderNode : public rclcpp::Node
{
public:
  COMPOSITION_PUBLIC
  explicit SenderNode(const rclcpp::NodeOptions & options);

protected:
  void timer_callback();

private:
  size_t count_;
  rclcpp::Publisher<friend_msgs::msg::FriendInfo>::SharedPtr pub_;
  rclcpp::TimerBase::SharedPtr timer_;
  friend_msgs::msg::FriendInfo message_;
};

}  // namespace composition

#endif  // COMPOSITION__HELLO_FRINED_PUB_COMPONENT_HPP_
