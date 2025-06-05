#include <rclcpp/rclcpp.hpp>
#include <friend_msgs/msg/friend_info.hpp>
#include <std_msgs/msg/header.hpp>
#include <friend_msgs/msg/temp_info.hpp>

#include <chrono>
#include <functional>
#include <memory>
#include <string>
// https://docs.ros.org/en/foxy/Tutorials/Beginner-Client-Libraries/Writing-A-Simple-Cpp-Publisher-And-Subscriber.html

using namespace std::chrono_literals;
 // TODO create timer that publish FriendInfo msg 10 times per second 
class SenderNode : public rclcpp::Node{
  public:
    SenderNode() : Node("SenderNode"){
        publisher_ = this->create_publisher<friend_msgs::msg::FriendInfo>("/r2d2_pose", 100);
        timer_ = this->create_wall_timer(
        500ms, std::bind(&SenderNode::timer_callback, this));
    }

    void timer_callback(){

      friend_msgs::msg::TempInfo temp_info;
      std_msgs::msg::Header header;
      header.stamp = this->now();
      temp_info.header = header;
      // RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", friend_info.name.c_str());
      // publisher_->publish(friend_info);

    }
  private:
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<friend_msgs::msg::FriendInfo>::SharedPtr publisher_;

};

int main(int argc, char** argv){
  rclcpp::init(argc, argv);

  auto node = std::make_shared<SenderNode>();
  
  rclcpp::spin(node);

  rclcpp::shutdown();
  return 0;
}