#include <vector>
#include <string>
#include <friend_msgs/msg/friend_info.hpp>
#include "rclcpp/rclcpp.hpp"

class SetUserInfo : public rclcpp::Node
{
public:
  SetUserInfo()
  : Node("set_user_info_node")
  {
    declare_parameter("user_name", "r2d2");

    param_subscriber_ = std::make_shared<rclcpp::ParameterEventHandler>(this);
    auto callback_linear_x = [this](const rclcpp::Parameter &p) {
      RCLCPP_INFO(this->get_logger(), "callback_linear_x: Received an update to parameter \"%s\" "
                  "of type %s: \"%s\"", p.get_name().c_str(), p.get_type_name().c_str(), p); 
      user_name_ = p;
    };
    cb_handle_ = param_subscriber_->add_parameter_callback("user_name", user_name_);

    declare_parameter("user_id", 345);
    declare_parameter("friends_names", std::vector<std::string>());
    declare_parameter("friends_ids", std::vector<int64_t>({}));

    get_parameter("user_name", user_name_);
    RCLCPP_INFO_STREAM(get_logger(), "User name: " << user_name_);

    get_parameter("user_id", user_id_);
    RCLCPP_INFO_STREAM(get_logger(), "User id: "<< user_id_);

    get_parameter("friends_names", frineds_names_);
    get_parameter("friends_ids", frineds_ids_);

    if (frineds_names_.size() != frineds_ids_.size()) {
      RCLCPP_ERROR( get_logger(), "Friend names (%zu) !=  ids (%zu) ", frineds_names_.size(), frineds_ids_.size());
    } else {
      RCLCPP_INFO_STREAM(get_logger(), "Number of friends: " << frineds_names_.size());
      for (size_t i = 0; i < frineds_names_.size(); i++) {
        RCLCPP_INFO_STREAM(get_logger(), "\t" << frineds_names_[i] << "\t - " << frineds_ids_[i]);
      }
    }
  }

private:
  std::string user_name_;
  int user_id_;
  std::vector<std::string> frineds_names_;
  std::vector<int64_t>  frineds_ids_;
  std::shared_ptr<rclcpp::ParameterEventHandler> param_subscriber_;
  std::shared_ptr<rclcpp::ParameterCallbackHandle> cb_handle_; 

};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);

  auto node = std::make_shared<SetUserInfo>();

  rclcpp::spin(node);

  rclcpp::shutdown();
  return 0;
}
