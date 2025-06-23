#include "rclcpp/rclcpp.hpp"
#include "tf2_ros/transform_broadcaster.h"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include <tf2/LinearMath/Quaternion.h>
#include "rclcpp/rclcpp.hpp"
#include "tf2_ros/static_transform_broadcaster.h"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include <tf2/LinearMath/Quaternion.h>

#if __has_include(<tf2_geometry_msgs/tf2_geometry_msgs.hpp>)
  #include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>
#else
  #include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#endif

#include <chrono>
using namespace std::chrono_literals;

class DynamicTransform : public rclcpp::Node
{
public:
  DynamicTransform()
  : Node("dynamic_transform_broadcaster")
  {
    broadcaster_ = std::make_shared<tf2_ros::TransformBroadcaster>(this);
    timer_ = this->create_wall_timer(100ms, std::bind(&DynamicTransform::timerCallback, this));  
  }

private:
  void timerCallback()
  {
    static double angle = 0.0;
    angle += 0.05;

    geometry_msgs::msg::TransformStamped base_to_wrist;
    base_to_wrist.header.stamp = this->now();
    base_to_wrist.header.frame_id = "base_link";
    base_to_wrist.child_frame_id = "wrist";

    base_to_wrist.transform.translation.x = 0.5;
    base_to_wrist.transform.translation.y = 0.0;
    base_to_wrist.transform.translation.z = 0.5;

    tf2::Quaternion q;
    q.setRPY(0, 0, angle);
    base_to_wrist.transform.rotation = tf2::toMsg(q);

    broadcaster_->sendTransform(base_to_wrist);
  }
  std::shared_ptr<tf2_ros::TransformBroadcaster> broadcaster_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<DynamicTransform>());
  rclcpp::shutdown();
}
