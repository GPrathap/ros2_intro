#include <vector>
#include <string>
#include <friend_msgs/msg/friend_info.hpp>
#include "rclcpp/rclcpp.hpp"

// https://docs.ros.org/en/foxy/Tutorials/Beginner-Client-Libraries/Using-Parameters-In-A-Class-CPP.html

class SetUserInfo : public rclcpp::Node
{
public:
  SetUserInfo()
  : Node("set_user_info_node")
  {
    
    // TODO declare parameter for friends_names(vector of string) and friends_ids (you need to decide the type and why)
    
    // TODO get the friends_names and friends_ids parameters 

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
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);

  auto node = std::make_shared<SetUserInfo>();

  rclcpp::spin(node);

  rclcpp::shutdown();
  return 0;
}
