
#include "rclcpp/rclcpp.hpp"
#include <friend_msgs/msg/friend_info.hpp>


// https://docs.ros.org/en/foxy/Concepts/About-Executors.html

using namespace std::chrono_literals;
using std::placeholders::_1;


class SenderNode : public rclcpp::Node{
  public:
    SenderNode() : Node("SenderNode"){
      
    }

  private:
    
};


class ReceiverNode : public rclcpp::Node{
  public:
    ReceiverNode() : Node("receiver_node"){

    }
    
  private:
   
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);

  // TODO create two nodes: first node for publishing FriendInfo msg 10 times per second, 
  // second node for subscribing to the publisher topic you created 
  auto node_pub = std::make_shared<SenderNode>();
  auto node_sub = std::make_shared<ReceiverNode>();

  // Create a rclcpp::executors::SingleThreadedExecutor and add those created nodes 
  // Check the difference between SingleThreadedExecutor and MultiThreadedExecutor
  
  rclcpp::shutdown();
  return 0;
}
