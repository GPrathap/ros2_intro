#include <rclcpp/rclcpp.hpp>
#include <friend_msgs/msg/friend_info.hpp>


using namespace std::chrono_literals;
class SenderNode : public rclcpp::Node{
  public:
  
    SenderNode() : Node("SenderNode"){
      publisher_ = create_publisher<friend_msgs::msg::FriendInfo>("/r2d2_pose", 10);
      timer_ = create_wall_timer(500ms, std::bind(&SenderNode::timer_callback, this));
    }

    void timer_callback(){
      message_.id = 345;
      message_.name = "d2r2";
      std::vector<int32_t> items = {4, 5, 67, 34};
      message_.food_items = {4 , 5 , 67, 34};
      publisher_->publish(message_);
    }
  
  private:
    rclcpp::Publisher<friend_msgs::msg::FriendInfo>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    friend_msgs::msg::FriendInfo message_;
};

int main(int argc, char** argv){
  rclcpp::init(argc, argv);

  auto node = std::make_shared<SenderNode>();
  

  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}