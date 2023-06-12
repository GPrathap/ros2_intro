#include <rclcpp/rclcpp.hpp>
#include <friend_msgs/msg/friend_info.hpp>

using namespace std::chrono_literals;

int main(int argc, char** argv){
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("publisher_node");
  
  auto publisher = node->create_publisher<friend_msgs::msg::FriendInfo>("/r2d2_pose", 10);

  rclcpp::Rate loop_rate(500ms);
  while(rclcpp::ok()){
    friend_msgs::msg::FriendInfo msg;
    msg.name = "r2d2";
    msg.id = 456;

    publisher->publish(msg);
    rclcpp::spin_some(node);
    loop_rate.sleep();
  } 
  rclcpp::shutdown();
  return 0;
}
