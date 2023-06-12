
#ifndef COMPOSITION__CLIENT_SERVICE_COMPONENT_HPP_
#define COMPOSITION__CLIENT_SERVICE_COMPONENT_HPP_

#include "composition/visibility_control.h"
#include <friend_msgs/srv/friend_info_service.hpp>
#include "rclcpp/rclcpp.hpp"

#include <cinttypes>
#include <iostream>
#include <memory>


namespace composition
{

class Client : public rclcpp::Node
{
public:
  COMPOSITION_PUBLIC
  explicit Client(const rclcpp::NodeOptions & options);

protected:
  void on_timer();

private:
  rclcpp::Client<friend_msgs::srv::FriendInfoService>::SharedPtr client_;
  rclcpp::TimerBase::SharedPtr timer_;
};

}  // namespace composition

#endif  // COMPOSITION__CLIENT_SERVICE_COMPONENT_HPP_
