#include <rclcpp/rclcpp.hpp>
// TODO import friend_info_service header 
#include <memory>
#include <chrono>
#include <cstdlib>

// https://docs.ros.org/en/foxy/Tutorials/Beginner-Client-Libraries/Writing-A-Simple-Cpp-Service-And-Client.html

using namespace std::chrono_literals;

// TODO create a service client with the name service_client
//     1). Call the service, i.e, set_heartbeat, that must be type of friend_msgs::srv::FriendInfoService
//     2). Set the id and value for the request, 
//     3). Check whether service is available or not 
//     4). If service is available send the request and print the response message  
//     5). If the service is unavailable print a warning message saying "service is not available"

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);

  if (argc != 2)
  {
    RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "usage: need id and value");
    return 1;
  }

  rclcpp::shutdown();
  return 0;
}
