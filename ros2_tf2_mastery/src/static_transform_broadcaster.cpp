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

// https://docs.ros.org/en/foxy/Tutorials/Intermediate/Tf2/Writing-A-Tf2-Static-Broadcaster-Cpp.html
class StaticTransform : public rclcpp::Node
{
public:
  StaticTransform()
  : Node("static_transform_broadcaster")
  {
    broadcaster_ = std::make_shared<tf2_ros::StaticTransformBroadcaster>(this);
    publishTransforms();
  }

private:
  void publishTransforms()
  {
    geometry_msgs::msg::TransformStamped base_to_arm;
    base_to_arm.header.stamp = this->now();
    base_to_arm.header.frame_id = "base_link";
    base_to_arm.child_frame_id = "arm_base";
    base_to_arm.transform.translation.x = 0.5;
    base_to_arm.transform.translation.y = 0.0;
    base_to_arm.transform.translation.z = 0.0;
    base_to_arm.transform.rotation = tf2::toMsg(tf2::Quaternion(0, 0, 0, 1));

    geometry_msgs::msg::TransformStamped wrist_to_camera;
    wrist_to_camera.header.stamp = this->now();
    wrist_to_camera.header.frame_id = "wrist";
    wrist_to_camera.child_frame_id = "camera";
    wrist_to_camera.transform.translation.x = 0.0;
    wrist_to_camera.transform.translation.y = 0.0;
    wrist_to_camera.transform.translation.z = 0.2;

    // 90 degree rotation about Z
    tf2::Quaternion q;
    q.setRPY(0, 0, M_PI/2);
    wrist_to_camera.transform.rotation = tf2::toMsg(q);

    broadcaster_->sendTransform({base_to_arm, wrist_to_camera});
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
