#ifndef COMPOSITION__SERVICE_SERVER_COMPONENT_HPP_
#define COMPOSITION__SERVICE_SERVER_COMPONENT_HPP_


#include "composition/visibility_control.h"
#include <friend_msgs/srv/friend_info_service.hpp>
#include "rclcpp/rclcpp.hpp"

#include <cinttypes>
#include <iostream>
#include <memory>

namespace composition
{

class Server : public rclcpp::Node
{
public:
  COMPOSITION_PUBLIC
  explicit Server(const rclcpp::NodeOptions & options);

private:
  rclcpp::Service<friend_msgs::srv::FriendInfoService>::SharedPtr service;
};

}  // namespace composition

#endif  // COMPOSITION__SERVICE_SERVER_COMPONENT_HPP_
