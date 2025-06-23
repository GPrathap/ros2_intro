
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/int32.hpp>
#include <geometry_msgs/msg/vector3.hpp>
#include <friend_msgs/srv/set_speed.hpp>
#include <math.h>
#include <memory>
#include <chrono>
#include <cstdlib>

using std::placeholders::_1; 
using std::placeholders::_2;

class HagenSub : public rclcpp::Node{
  public:
    HagenSub(): Node("hagen_sub"){
      temp_sub_ = create_subscription<std_msgs::msg::Int32>("/joy_hagen/temperature", 10, std::bind(&HagenSub::callbackTemp, this, _1));
      acc_sub_ = create_subscription<geometry_msgs::msg::Vector3>("/joy_hagen/imu", 10, std::bind(&HagenSub::callbackAcc, this, _1));
      service_set_speed_ = this->create_service<friend_msgs::srv::SetSpeed>("/speed", std::bind(&HagenSub::callbackSpeed, this, _1, _2));
    }

    void callbackTemp(const std_msgs::msg::Int32::SharedPtr msg){
      RCLCPP_INFO_STREAM(get_logger(), "Temp = " << msg->data );
    }

    void callbackAcc(const geometry_msgs::msg::Vector3::SharedPtr msg){
      RCLCPP_INFO_STREAM(get_logger(),  "Acc = (" << msg->x << ", " << msg->y << ", " << msg->z << ")");
    }

    bool callbackSpeed(std::shared_ptr<friend_msgs::srv::SetSpeed::Request> req, std::shared_ptr<friend_msgs::srv::SetSpeed::Response> res){
      RCLCPP_INFO_STREAM(get_logger(), "Speed service request: desired speed = " << req->desired_speed);
      // TODO set res.new_speed 0.6 times desired_speed 
      // TODO set previous_speed as res.new_speed
      res->stalled = new_speed < 0.1;
      previous_speed = new_speed;
      return true;
    }

    private:
      float previous_speed = 0.;
      float new_speed      = 0.;
      rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr temp_sub_;
      rclcpp::Subscription<geometry_msgs::msg::Vector3>::SharedPtr acc_sub_;
      rclcpp::Service<friend_msgs::srv::SetSpeed>::SharedPtr service_set_speed_;
};


int main( int argc, char **argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<HagenSub>();
  rclcpp::spin(node);
  return EXIT_SUCCESS;
}

