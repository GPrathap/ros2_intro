#include <rclcpp/rclcpp.hpp>
#include <friend_msgs/msg/friend_info.hpp>

// https://docs.ros.org/en/foxy/Tutorials/Beginner-Client-Libraries/Writing-A-Simple-Cpp-Publisher-And-Subscriber.html

using namespace std::chrono_literals;
 // TODO create timer that publish FriendInfo msg 10 times per second 
class SenderNode : public rclcpp::Node{
  public:
    SenderNode() : Node("SenderNode"){
      
    }
  private:

};

int main(int argc, char** argv){
  rclcpp::init(argc, argv);

  auto node = std::make_shared<SenderNode>();
  
  rclcpp::spin(node);

  rclcpp::shutdown();
  return 0;
}