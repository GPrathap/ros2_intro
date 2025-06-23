// ================================
// 🚀 Mission Stardust ROS 2 Lab
// File: rover_viz_lab.cpp (Main Entry)
// ================================

#include "rclcpp/rclcpp.hpp"
#include "visualization_msgs/msg/marker.hpp"
#include "visualization_msgs/msg/marker_array.hpp"
#include "geometry_msgs/msg/point.hpp"
#include "sensor_msgs/msg/point_cloud2.hpp"
#include "sensor_msgs/msg/imu.hpp"
#include "nav_msgs/msg/odometry.hpp"
#include "tf2_ros/transform_broadcaster.h"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include <chrono>
#include <random>
#include <memory>

using namespace std::chrono_literals;

class RoverVizLab : public rclcpp::Node {
public:
  RoverVizLab() : Node("rover_viz_lab") {
    // Marker for status beacon
    
    // MarkerArray for rocks
    
    // PointCloud2 for simulated LiDAR
  
    // Odometry

    // IMU
    

    // TODO: Add service or parameter to toggle visualization layers on/off at runtime
    // TODO: Load rock sample positions from YAML file for realism
    // TODO: Generate realistic LiDAR scan using PCL or sensor model
    // TODO: Visualize trajectory history using Line Strip marker
    // TODO: Add covariance matrices to IMU and Odometry messages
  }

private:
  rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr marker_pub_;
  rclcpp::Publisher<visualization_msgs::msg::MarkerArray>::SharedPtr rock_pub_;
  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr cloud_pub_;
  rclcpp::Publisher<nav_msgs::msg::Odometry>::SharedPtr odom_pub_;
  rclcpp::Publisher<sensor_msgs::msg::Imu>::SharedPtr imu_pub_;
  std::shared_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;

  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::TimerBase::SharedPtr odom_timer_;
  rclcpp::TimerBase::SharedPtr imu_timer_;

  int status_ = 0;
  double x_ = 0.0, y_ = 0.0, yaw_ = 0.0;

  void publish_marker() {
    
  }

  void publish_rock_array() {
    
  }

  void publish_lidar_cloud() {
    
  }

  void publish_odometry() {
   
  }

  void publish_imu() {
   
  }
};

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<RoverVizLab>());
  rclcpp::shutdown();
  return 0;
}
