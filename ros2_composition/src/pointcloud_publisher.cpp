#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/point_cloud2.hpp"
#include "sensor_msgs/point_cloud2_iterator.hpp"
#include "rclcpp_components/register_node_macro.hpp"


class PointCloudPublisher : public rclcpp::Node {
public:
 PointCloudPublisher(const rclcpp::NodeOptions &options) : Node("pointcloud_publisher", options) {
  
  
   // rclcpp::QoS qos_profile(rclcpp::QoSInitialization::from_rmw(rmw_qos_profile_sensor_data));
   // qos_profile.reliable().best_effort();  // or .reliable()
   // qos_profile.durability_volatile();     // or .transient_local()


   // auto qos = rclcpp::QoS(rclcpp::KeepLast(10))
   //          .best_effort() // or .reliable()
   //          .durability_volatile();  // or .transient_local()


   auto qos = rclcpp::SensorDataQoS();  // depth=5, best_effort, volatile, keep_last
   publisher_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("cloud", qos);


   timer_ = this->create_wall_timer(std::chrono::milliseconds(100), [this]() {
     auto msg = generate_pointcloud();
     publisher_->publish(msg);
   });
 }


private:
 rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr publisher_;
 rclcpp::TimerBase::SharedPtr timer_;


 sensor_msgs::msg::PointCloud2 generate_pointcloud() {
   sensor_msgs::msg::PointCloud2 cloud_msg;
   cloud_msg.header.stamp = this->now();
   cloud_msg.header.frame_id = "map";


   cloud_msg.height = 1;
   cloud_msg.width = 100000;  // 100k points


   sensor_msgs::PointCloud2Modifier modifier(cloud_msg);
   modifier.setPointCloud2FieldsByString(1, "xyz");
   modifier.resize(cloud_msg.width);


   sensor_msgs::PointCloud2Iterator<float> iter_x(cloud_msg, "x");
   sensor_msgs::PointCloud2Iterator<float> iter_y(cloud_msg, "y");
   sensor_msgs::PointCloud2Iterator<float> iter_z(cloud_msg, "z");


   for (size_t i = 0; i < cloud_msg.width; ++i, ++iter_x, ++iter_y, ++iter_z) {
     *iter_x = static_cast<float>(i % 1000);
     *iter_y = static_cast<float>(i / 1000);
     *iter_z = 0.0f;
   }


   return cloud_msg;
 }
};




RCLCPP_COMPONENTS_REGISTER_NODE(PointCloudPublisher)
