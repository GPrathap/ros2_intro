
#include <rclcpp/rclcpp.hpp>
#include <math.h>
#include <memory>
#include <chrono>
#include <cstdlib>
#include <visualization_msgs/msg/marker.hpp>

using namespace std::chrono_literals;

class HagenPubMarkerArray : public rclcpp::Node{
  public:
    HagenPubMarkerArray(): Node("hagen_pub_marker_array"){
      marker_pub_ = create_publisher<visualization_msgs::msg::Marker>("/joy_hagen_marker_array/marker", 10);
    }

    void sendMessages(){

      visualization_msgs::msg::Marker msg_marker;
      // TODO set header frame id of msg_marker as the "marker_frame"
      msg_marker.header.frame_id = "marker_frame";
      msg_marker.ns = "shapes";
      msg_marker.id = 0;
      msg_marker.type = visualization_msgs::msg::Marker::CUBE;
      msg_marker.action = visualization_msgs::msg::Marker::ADD;
      // TODO set msg_marker type and actions as  visualization_msgs::Marker::CUBE and visualization_msgs::Marker::ADD ,
      // respectively 

      msg_marker.pose.position.x = 0.;
      msg_marker.pose.position.y = 1.;
      msg_marker.pose.position.z = 2.;
      msg_marker.pose.orientation.x = 0.;
      msg_marker.pose.orientation.y = 0.;
      msg_marker.pose.orientation.z = 0.;
      msg_marker.pose.orientation.w = 1.;

      msg_marker.scale.x = 1.;
      msg_marker.scale.y = 1.;
      msg_marker.scale.z = 1.;

      msg_marker.color.r = 1.;
      msg_marker.color.g = 0.;
      msg_marker.color.b = 0.;
      msg_marker.color.a = 1.;

      msg_marker.lifetime = rclcpp::Duration::from_seconds(0.0);
      RCLCPP_INFO(get_logger(), "Initial Marker Created");
      rclcpp::Rate rate(1s);
      while( rclcpp::ok() ) {
        // Set msg_marker header time stamp as 
        // msg_marker.header.stamp = 
        msg_marker.pose.position.x += 0.01;
        msg_marker.type = visualization_msgs::msg::Marker::SPHERE;
        msg_marker.pose.position.y += 0.02;
        msg_marker.pose.position.z += 0.03;
        marker_pub_->publish( msg_marker );
        rclcpp::spin_some(this->get_node_base_interface());
        rate.sleep();
      }
    }
    private:
      float previous_speed = 0.;
      float new_speed      = 0.;
      rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr marker_pub_;
};


int main( int argc, char **argv )
{
  rclcpp::init( argc, argv);
  auto node = std::make_shared<HagenPubMarkerArray>();
  node->sendMessages();
  rclcpp::spin(node);
  return 0;
}