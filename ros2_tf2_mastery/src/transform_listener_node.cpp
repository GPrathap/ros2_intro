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
  : Node("transform_listener"),
    buffer_(get_clock()),
    listener_(buffer_)
  {
    timer_ = this->create_wall_timer(500ms, std::bind(&TransformListener::onTimer, this));  
  }
  
private:
  void onTimer()
  {
    try
    {
      geometry_msgs::msg::TransformStamped base_to_camera = 
        buffer_.lookupTransform("base_link", "arm_base", rclcpp::Time(0));

      RCLCPP_INFO(this->get_logger(), "Base->Camera: x: %f y: %f z: %f",
                   base_to_camera.transform.translation.x,
                   base_to_camera.transform.translation.y,
                   base_to_camera.transform.translation.z);
    }
    catch (const tf2::TransformException & ex)
    {
      RCLCPP_WARN(this->get_logger(), "Transform unavailable: %s", ex.what()); 
    }
  }
  
  tf2_ros::Buffer buffer_;
  tf2_ros::TransformListener listener_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<TransformListener>());
  rclcpp::shutdown();
}

