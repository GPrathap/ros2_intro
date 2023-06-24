#include "rclcpp/rclcpp.hpp"
#include <buggy/msg/custom_msg.h>
#include <buggy/srv/custom_srv.h>
#include<iostream>

using std::placeholders::_1; 

bool flag  = false;
bool flag2 = false;

void callback(const buggy::CustomMsg::ConstPtr& msg)
{
	flag = msg->flag.data;
}

bool turnOn(buggy::CustomSrv::Request& req, buggy::CustomSrv::Response& res) {
  flag2 = req.flag.data;
  res.result.data = flag2;
  return true;
}

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  
  auto node = rclcpp::Node::make_shared("pub");
  rclcpp::Subscription<buggy::msg::CustomMsg>::SharedPtr subscriber_;
  subscriber_ = create_subscription<buggy::msg::CustomMsg>("/topic", 10
      ,std::bind(&callback, _1));

  rclcpp::Service<friend_msgs::srv::FriendInfoService>::SharedPtr turn_on_service_ = 
    node->create_service<friend_msgs::srv::FriendInfoService>("turnon", &turnon);

  rclcpp::Rate loop_rate(500ms);
  while(rclcpp::ok()){
    if(flag && flag2)
      std::cout << "You finished, congrats on 5 points\n";
    rclcpp::spin_some(node);
    loop_rate.sleep();
  }  
  rclcpp::shutdown();
  return 0;
}

