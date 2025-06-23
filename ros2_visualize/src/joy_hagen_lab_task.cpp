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
    marker_pub_ = this->create_publisher<visualization_msgs::msg::Marker>("/rover/status_marker", 10);
    timer_ = this->create_wall_timer(2s, std::bind(&RoverVizLab::publish_marker, this));

    // MarkerArray for rocks
    rock_pub_ = this->create_publisher<visualization_msgs::msg::MarkerArray>("/rover/rock_samples", 10);
    publish_rock_array();

    // PointCloud2 for simulated LiDAR
    cloud_pub_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("/rover/lidar_points", 10);
    publish_lidar_cloud();

    // Odometry
    odom_pub_ = this->create_publisher<nav_msgs::msg::Odometry>("/rover/odom", 10);
    tf_broadcaster_ = std::make_shared<tf2_ros::TransformBroadcaster>(*this);
    odom_timer_ = this->create_wall_timer(100ms, std::bind(&RoverVizLab::publish_odometry, this));

    // IMU
    imu_pub_ = this->create_publisher<sensor_msgs::msg::Imu>("/rover/imu", 10);
    imu_timer_ = this->create_wall_timer(200ms, std::bind(&RoverVizLab::publish_imu, this));

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
    visualization_msgs::msg::Marker marker;
    marker.header.frame_id = "base_link";
    marker.header.stamp = this->now();
    marker.ns = "status";
    marker.id = 0;
    marker.type = visualization_msgs::msg::Marker::SPHERE;
    marker.action = visualization_msgs::msg::Marker::ADD;
    marker.pose.position.z = 1.0;
    marker.scale.x = marker.scale.y = marker.scale.z = 0.3;

    if (status_ == 0) {
      marker.color.r = 0.0; marker.color.g = 0.0; marker.color.b = 1.0; marker.color.a = 1.0;
    } else if (status_ == 1) {
      marker.color.r = 0.0; marker.color.g = 1.0; marker.color.b = 0.0; marker.color.a = 1.0;
    } else {
      marker.color.r = 1.0; marker.color.g = 0.0; marker.color.b = 0.0; marker.color.a = 1.0;
    }
    status_ = (status_ + 1) % 3;

    marker_pub_->publish(marker);
  }

  void publish_rock_array() {
    visualization_msgs::msg::MarkerArray marker_array;
    for (int i = 0; i < 6; ++i) {
      visualization_msgs::msg::Marker rock;
      rock.header.frame_id = "map";
      rock.header.stamp = this->now();
      rock.ns = "rocks";
      rock.id = i;
      rock.type = visualization_msgs::msg::Marker::CUBE;
      rock.action = visualization_msgs::msg::Marker::ADD;
      rock.pose.position.x = i * 0.5;
      rock.pose.position.y = 1.5;
      rock.pose.position.z = 0.1;
      rock.scale.x = rock.scale.y = rock.scale.z = 0.2;
      rock.color.r = 1.0; rock.color.g = 0.5; rock.color.b = 0.0; rock.color.a = 1.0;
      marker_array.markers.push_back(rock);
    }
    rock_pub_->publish(marker_array);
  }

  void publish_lidar_cloud() {
    // Placeholder for real point cloud generation
    sensor_msgs::msg::PointCloud2 cloud;
    cloud.header.frame_id = "base_link";
    cloud.header.stamp = this->now();
    cloud.height = 1;
    cloud.width = 0;
    cloud.is_dense = false;
    cloud.is_bigendian = false;
    // TODO: Fill cloud data with realistic LiDAR point simulation using PCL
    cloud_pub_->publish(cloud); // Publish empty for now
  }

  void publish_odometry() {
    x_ += 0.01; yaw_ += 0.01;
    nav_msgs::msg::Odometry odom;
    odom.header.frame_id = "odom";
    odom.child_frame_id = "base_link";
    odom.header.stamp = this->now();
    odom.pose.pose.position.x = x_;
    odom.pose.pose.position.y = y_;
    odom.pose.pose.orientation.z = sin(yaw_ / 2);
    odom.pose.pose.orientation.w = cos(yaw_ / 2);

    geometry_msgs::msg::TransformStamped tf;
    tf.header = odom.header;
    tf.child_frame_id = odom.child_frame_id;
    tf.transform.translation.x = x_;
    tf.transform.translation.y = y_;
    tf.transform.rotation = odom.pose.pose.orientation;

    tf_broadcaster_->sendTransform(tf);
    odom_pub_->publish(odom);
  }

  void publish_imu() {
    sensor_msgs::msg::Imu imu;
    imu.header.frame_id = "base_link";
    imu.header.stamp = this->now();
    imu.orientation.z = sin(yaw_ / 2);
    imu.orientation.w = cos(yaw_ / 2);
    imu_pub_->publish(imu);
  }
};

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<RoverVizLab>());
  rclcpp::shutdown();
  return 0;
}
