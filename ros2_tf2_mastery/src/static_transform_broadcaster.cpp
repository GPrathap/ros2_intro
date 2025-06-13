#include "rclcpp/rclcpp.hpp"
#include "tf2_ros/static_transform_broadcaster.h"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>  // For tf2::toMsg

#include <chrono>
using namespace std::chrono_literals;

// https://docs.ros.org/en/foxy/Tutorials/Intermediate/Tf2/Writing-A-Tf2-Static-Broadcaster-Cpp.html
class StaticTransform : public rclcpp::Node
{
public:
  StaticTransform()
  : Node("static_transform_broadcaster")
  {
    
  }

private:
  void publishTransforms()
  {
    
  }
  std::shared_ptr<tf2_ros::StaticTransformBroadcaster> broadcaster_;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  std::shared_ptr<StaticTransform> static_broad_caster = std::make_shared<StaticTransform>();
  rclcpp::spin(static_broad_caster);
  rclcpp::shutdown();
}
