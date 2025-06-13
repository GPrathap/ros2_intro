#include "rclcpp/rclcpp.hpp"
#include "tf2_ros/buffer.h"
#include "tf2_ros/transform_listener.h"
#include "geometry_msgs/msg/transform_stamped.hpp"

#include <chrono>
using namespace std::chrono_literals;

class TransformListener : public rclcpp::Node
{
public:
  TransformListener()
  : Node("transform_listener")
  {

  }
  
private:
  void onTimer()
  {
    
  }
  
  // tf2_ros::Buffer buffer_;
  // tf2_ros::TransformListener listener_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<TransformListener>());
  rclcpp::shutdown();
}

