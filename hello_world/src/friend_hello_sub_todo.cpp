#include "rclcpp/rclcpp.hpp"
#include <friend_msgs/msg/friend_info.hpp>

using std::placeholders::_1; 

class ReceiverNode : public rclcpp::Node{
  public:
    ReceiverNode() : Node("receiver_node"){
      subscriber_ = create_subscription<friend_msgs::msg::FriendInfo>("/r2d2_pose", 10
      ,std::bind(&ReceiverNode::callback, this, _1));
    }
    void callback(const friend_msgs::msg::FriendInfo::SharedPtr msg);
  private:
    rclcpp::Subscription<friend_msgs::msg::FriendInfo>::SharedPtr subscriber_;
};


void ReceiverNode::callback(const friend_msgs::msg::FriendInfo::SharedPtr msg)
{
  RCLCPP_INFO(get_logger(), "Hello %d", msg->id);
  std::vector<int32_t> items = msg->food_items;
  for(auto food_item: items){
    std::cout<<  food_item << ",";
  }
  std::cout<< std::endl;
}

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<ReceiverNode>();
  
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}

