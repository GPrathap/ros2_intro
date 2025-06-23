
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <nav_msgs/msg/odometry.hpp>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_ros/static_transform_broadcaster.h>

// https://github.com/ros-perception/perception_pcl
// http://wiki.ros.org/navigation/Tutorials/RobotSetup/Odom

using namespace std::chrono_literals;

class PointCloudPublisher : public rclcpp::Node{
  public:
    PointCloudPublisher() : Node("point_cloud_publisher"){
      pc_pub = create_publisher<sensor_msgs::msg::PointCloud2>("/joy_hagen_point_cloud/point_cloud", 1000);
      odom_pub = create_publisher<nav_msgs::msg::Odometry>("/odom", 50);

    }

    void generatePointCloud(){
        pc.width  = 200;
        pc.height = 100;
        pc.is_dense = false;
        pc.resize(pc.width*pc.height);
        // TODO resize the pc with its size 
        for( size_t i = 0; i < pc.height; ++i ) {
          for( size_t j = 0; j < pc.width; ++j ) {
            const size_t k = pc.width * i + j;
            // TODO assign the x, y, and z values of each point
              pc.points[k].x = 0.1 * (i+1);
              pc.points[k].y = 0.2 * (j+1);
              pc.points[k].z = 1.5;
          }
        }
    }

    void updateAndPublishPC(){
      RCLCPP_INFO( get_logger(), "Initial Point Cloud created." );
      rclcpp::Rate rate(1s);

      double pose_x = 0;
      double pose_y = 0;
      double pose_z = 0;
      while( rclcpp::ok() ) {
        for( size_t i = 0; i < pc.height; ++i ) {
          for( size_t j = 0; j < pc.width; ++j ) {
            const size_t k = pc.width * i + j;
            // TODO assign the x, y, and z values of each point
            pc.points[k].z -= 0.1;  
          }
        }

        pose_x += 0.5;
        pose_y += 0.5;

        nav_msgs::msg::Odometry odom;
        odom.header.frame_id = "odom";

        //set the position
        odom.pose.pose.position.x = pose_x;
        odom.pose.pose.position.y = pose_y;
        odom.pose.pose.position.z = pose_z;
        sensor_msgs::msg::PointCloud2 msg_pc;
        pcl::toROSMsg(pc, msg_pc);
        // TODO use pcl::toROSMsg to convert pcl message to ROS message 
        // TODO set header frame id of msg_pc as the "pc_frame"
        msg_pc.header.frame_id = "pc_frame";
        msg_pc.header.stamp = this->get_clock()->now();
        pc_pub->publish(msg_pc);
        odom_pub->publish(odom);
        rclcpp::spin_some(this->get_node_base_interface());
        rate.sleep();
      }
    }
  
  private:
    rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr pc_pub;
    rclcpp::Publisher<nav_msgs::msg::Odometry>::SharedPtr odom_pub;
    pcl::PointCloud<pcl::PointXYZ> pc;
    
};

int main( int argc, char **argv )
{
  rclcpp::init( argc, argv);
  auto node = std::make_shared<PointCloudPublisher>();
  node->generatePointCloud();
  node->updateAndPublishPC();
  rclcpp::spin(node);
  return 0;
}

