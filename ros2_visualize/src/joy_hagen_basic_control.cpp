// ref https://github.com/ros-visualization/visualization_tutorials/tree/ros2/interactive_marker_tutorials

#include <chrono>
#include <memory>
#include <string>

#include <interactive_markers/interactive_marker_server.hpp>
#include <interactive_markers/menu_handler.hpp>
#include <rclcpp/rclcpp.hpp>
#include <tf2/LinearMath/Transform.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2/LinearMath/Vector3.h>
#include <tf2/transform_datatypes.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>
#include <tf2_ros/transform_broadcaster.h>
#include <visualization_msgs/msg/interactive_marker.hpp>
#include <visualization_msgs/msg/interactive_marker_control.hpp>
#include <visualization_msgs/msg/interactive_marker_feedback.hpp>
#include <visualization_msgs/msg/marker.hpp>


using std::placeholders::_1;

namespace interactive_marker_tutorials
{

class BasicControl : public rclcpp::Node
{
public:
  explicit BasicControl(const rclcpp::NodeOptions & options = rclcpp::NodeOptions());

  ~BasicControl() = default;

  inline void
  applyChanges()
  {
    server_->applyChanges();
  }

  visualization_msgs::msg::Marker
  makeBox(const visualization_msgs::msg::InteractiveMarker & msg);

  visualization_msgs::msg::InteractiveMarkerControl &
  makeBoxControl(visualization_msgs::msg::InteractiveMarker & msg);

  void
  make6DofMarker(
    bool fixed, unsigned int interaction_mode, const tf2::Vector3 & position, bool show_6dof);

  

private:
  void
  frameCallback();

  void
  processFeedback(
    const visualization_msgs::msg::InteractiveMarkerFeedback::ConstSharedPtr & feedback);


  std::unique_ptr<interactive_markers::InteractiveMarkerServer> server_;
  interactive_markers::MenuHandler menu_handler_;
  std::unique_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
  rclcpp::TimerBase::SharedPtr frame_timer_;
};  // class BasicControl

BasicControl::BasicControl(const rclcpp::NodeOptions & options)
: rclcpp::Node("basic_controls", options),
  menu_handler_()
{
  server_ = std::make_unique<interactive_markers::InteractiveMarkerServer>(
    "basic_controls",
    get_node_base_interface(),
    get_node_clock_interface(),
    get_node_logging_interface(),
    get_node_topics_interface(),
    get_node_services_interface());

  menu_handler_.insert("First Entry", std::bind(&BasicControl::processFeedback, this, _1));
  menu_handler_.insert("Second Entry", std::bind(&BasicControl::processFeedback, this, _1));
  interactive_markers::MenuHandler::EntryHandle sub_menu_handle = menu_handler_.insert("Submenu");
  menu_handler_.insert(
    sub_menu_handle, "First Entry", std::bind(&BasicControl::processFeedback, this, _1));
  menu_handler_.insert(
    sub_menu_handle, "Second Entry", std::bind(&BasicControl::processFeedback, this, _1));

  // create a timer to update the published transforms
  frame_timer_ = create_wall_timer(
    std::chrono::milliseconds(10), std::bind(&BasicControl::frameCallback, this));
}

visualization_msgs::msg::Marker
BasicControl::makeBox(const visualization_msgs::msg::InteractiveMarker & msg)
{
  visualization_msgs::msg::Marker marker;

  marker.type = visualization_msgs::msg::Marker::CUBE;
  marker.scale.x = msg.scale * 0.45;
  marker.scale.y = msg.scale * 0.45;
  marker.scale.z = msg.scale * 0.45;
  marker.color.r = 0.5;
  marker.color.g = 0.5;
  marker.color.b = 0.5;
  marker.color.a = 1.0;

  return marker;
}

visualization_msgs::msg::InteractiveMarkerControl &
BasicControl::makeBoxControl(visualization_msgs::msg::InteractiveMarker & msg)
{
  visualization_msgs::msg::InteractiveMarkerControl control;
  control.always_visible = true;
  control.markers.push_back(makeBox(msg));
  msg.controls.push_back(control);

  return msg.controls.back();
}

void
BasicControl::frameCallback()
{
  static uint32_t counter = 0;

  if (!tf_broadcaster_) {
    tf_broadcaster_ = std::make_unique<tf2_ros::TransformBroadcaster>(shared_from_this());
  }

  tf2::TimePoint tf_time_point(std::chrono::nanoseconds(this->get_clock()->now().nanoseconds()));

  tf2::Stamped<tf2::Transform> transform;
  transform.stamp_ = tf_time_point;
  transform.frame_id_ = "base_link";
  transform.setOrigin(tf2::Vector3(0.0, 0.0, sin(static_cast<double>(counter) / 140.0) * 2.0));
  transform.setRotation(tf2::Quaternion(0.0, 0.0, 0.0, 1.0));

  geometry_msgs::msg::TransformStamped transform_msg;
  transform_msg = tf2::toMsg(transform);
  transform_msg.child_frame_id = "moving_frame";
  tf_broadcaster_->sendTransform(transform_msg);

  transform.setOrigin(tf2::Vector3(0.0, 0.0, 0.0));
  tf2::Quaternion quat;
  quat.setRPY(0.0, static_cast<double>(counter) / 140.0, 0.0);
  transform.setRotation(quat);
  transform_msg = tf2::toMsg(transform);
  transform_msg.child_frame_id = "rotating_frame";
  tf_broadcaster_->sendTransform(transform_msg);

  counter++;
}

void
BasicControl::processFeedback(
  const visualization_msgs::msg::InteractiveMarkerFeedback::ConstSharedPtr & feedback)
{
  std::ostringstream oss;
  oss << "Feedback from marker '" << feedback->marker_name << "' " <<
    " / control '" << feedback->control_name << "'";

  std::ostringstream mouse_point_ss;
  if (feedback->mouse_point_valid) {
    mouse_point_ss << " at " << feedback->mouse_point.x <<
      ", " << feedback->mouse_point.y <<
      ", " << feedback->mouse_point.z <<
      " in frame " << feedback->header.frame_id;
  }

  switch (feedback->event_type) {
    case visualization_msgs::msg::InteractiveMarkerFeedback::BUTTON_CLICK:
      oss << ": button click" << mouse_point_ss.str() << ".";
      RCLCPP_INFO(get_logger(), "%s", oss.str().c_str());
      break;

    case visualization_msgs::msg::InteractiveMarkerFeedback::MENU_SELECT:
      oss << ": menu item " << feedback->menu_entry_id << " clicked" << mouse_point_ss.str() << ".";
      RCLCPP_INFO(get_logger(), "%s", oss.str().c_str());
      break;

    case visualization_msgs::msg::InteractiveMarkerFeedback::POSE_UPDATE:
      oss << ": pose changed" <<
        "\nposition = " <<
        feedback->pose.position.x <<
        ", " << feedback->pose.position.y <<
        ", " << feedback->pose.position.z <<
        "\norientation = " <<
        feedback->pose.orientation.w <<
        ", " << feedback->pose.orientation.x <<
        ", " << feedback->pose.orientation.y <<
        ", " << feedback->pose.orientation.z <<
        "\nframe: " << feedback->header.frame_id <<
        " time: " << feedback->header.stamp.sec << "sec, " <<
        feedback->header.stamp.nanosec << " nsec";
      RCLCPP_INFO(get_logger(), "%s", oss.str().c_str());
      break;

    case visualization_msgs::msg::InteractiveMarkerFeedback::MOUSE_DOWN:
      oss << ": mouse down" << mouse_point_ss.str() << ".";
      RCLCPP_INFO(get_logger(), "%s", oss.str().c_str());
      break;

    case visualization_msgs::msg::InteractiveMarkerFeedback::MOUSE_UP:
      oss << ": mouse up" << mouse_point_ss.str() << ".";
      RCLCPP_INFO(get_logger(), "%s", oss.str().c_str());
      break;
  }
  server_->applyChanges();
}


void
BasicControl::make6DofMarker(
  bool fixed, unsigned int interaction_mode, const tf2::Vector3 & position, bool show_6dof)
{
  visualization_msgs::msg::InteractiveMarker int_marker;
  int_marker.header.frame_id = "base_link";
  int_marker.pose.position.x = position.getX();
  int_marker.pose.position.y = position.getY();
  int_marker.pose.position.z = position.getZ();
  int_marker.scale = 1;

  int_marker.name = "simple_6dof";
  int_marker.description = "Simple 6-DOF Control";

  // insert a box
  makeBoxControl(int_marker);
  int_marker.controls[0].interaction_mode = interaction_mode;

  visualization_msgs::msg::InteractiveMarkerControl control;
  if (interaction_mode != visualization_msgs::msg::InteractiveMarkerControl::NONE) {
    std::string mode_text = "NONE";
      if (interaction_mode == visualization_msgs::msg::InteractiveMarkerControl::MOVE_ROTATE_3D) {
        mode_text = "MOVE_ROTATE_3D";
      }
      int_marker.name += "_" + mode_text;
      int_marker.description = std::string("3D Control") + (show_6dof ? " + 6-DOF controls" : "") +
      "\n" + mode_text;
  }

  if (show_6dof) {
    tf2::Quaternion orien(1.0, 0.0, 0.0, 1.0);
    orien.normalize();
    control.orientation = tf2::toMsg(orien);
    control.name = "rotate_x";
    control.interaction_mode = visualization_msgs::msg::InteractiveMarkerControl::ROTATE_AXIS;
    int_marker.controls.push_back(control);
    control.name = "move_x";
    control.interaction_mode = visualization_msgs::msg::InteractiveMarkerControl::MOVE_AXIS;
    int_marker.controls.push_back(control);

    orien = tf2::Quaternion(0.0, 1.0, 0.0, 1.0);
    orien.normalize();
    control.orientation = tf2::toMsg(orien);
    control.name = "rotate_z";
    control.interaction_mode = visualization_msgs::msg::InteractiveMarkerControl::ROTATE_AXIS;
    int_marker.controls.push_back(control);
    control.name = "move_z";
    control.interaction_mode = visualization_msgs::msg::InteractiveMarkerControl::MOVE_AXIS;
    int_marker.controls.push_back(control);

    orien = tf2::Quaternion(0.0, 0.0, 1.0, 1.0);
    orien.normalize();
    control.orientation = tf2::toMsg(orien);
    control.name = "rotate_y";
    control.interaction_mode = visualization_msgs::msg::InteractiveMarkerControl::ROTATE_AXIS;
    int_marker.controls.push_back(control);
    control.name = "move_y";
    control.interaction_mode = visualization_msgs::msg::InteractiveMarkerControl::MOVE_AXIS;
    int_marker.controls.push_back(control);
  }

  server_->insert(int_marker);
  server_->setCallback(int_marker.name, std::bind(&BasicControl::processFeedback, this, _1));
  if (interaction_mode != visualization_msgs::msg::InteractiveMarkerControl::NONE) {
    menu_handler_.apply(*server_, int_marker.name);
  }
}

}  

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);

  auto basic_controls = std::make_shared<interactive_marker_tutorials::BasicControl>();
  tf2::Vector3 position(0, 0, 1);
  basic_controls->make6DofMarker(
    false, visualization_msgs::msg::InteractiveMarkerControl::MOVE_ROTATE_3D, position, true);
  basic_controls->applyChanges();

  rclcpp::executors::SingleThreadedExecutor executor;
  executor.add_node(basic_controls);
  RCLCPP_INFO(basic_controls->get_logger(), "Ready");
  executor.spin();
  rclcpp::shutdown();

  return 0;
}