#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/point_cloud2.hpp"
#include "rclcpp_components/register_node_macro.hpp"


class PointCloudSubscriber : public rclcpp::Node {
public:
 PointCloudSubscriber(const rclcpp::NodeOptions &options) : Node("pointcloud_subscriber", options) {
   auto qos = rclcpp::SensorDataQoS();  // depth=5, best_effort, volatile, keep_last
   subscription_ = this->create_subscription<sensor_msgs::msg::PointCloud2>(
     "cloud", qos,
     [this](sensor_msgs::msg::PointCloud2::SharedPtr msg) {
       rclcpp::Time now = this->now();
       rclcpp::Time sent = msg->header.stamp;
       double latency_ms = (now - sent).seconds() * 1000.0;
       RCLCPP_INFO(this->get_logger(), "Received %d points with latency %.2f ms", msg->width, latency_ms);
     });
 }


private:
 rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr subscription_;
};


RCLCPP_COMPONENTS_REGISTER_NODE(PointCloudSubscriber)




