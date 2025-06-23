
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/int32.hpp>
#include <geometry_msgs/msg/vector3.hpp>
#include <friend_msgs/srv/set_speed.hpp>
#include <math.h>
#include <memory>
#include <chrono>
#include <cstdlib>


using std::placeholders::_1; 
using std::placeholders::_2;
using namespace std::chrono_literals;

class HagenPub : public rclcpp::Node{
  public:
    HagenPub(): Node("hagen_pub"){
      temp_pub_ = create_publisher<std_msgs::msg::Int32>("/joy_hagen/temperature", 10);
      acc_pub_ = create_publisher<geometry_msgs::msg::Vector3>("/joy_hagen/imu", 10);
      client_get_speed_ = this->create_client<friend_msgs::srv::SetSpeed>("/speed");
    }

    void sendMessages(){
      // TODO define message types 
      std_msgs::msg::Int32 temp_data;
      geometry_msgs::msg::Vector3 imu_data;
      friend_msgs::srv::SetSpeed speed_srv;
      int i = 0;
      rclcpp::Rate rate(200ms);
      while( rclcpp::ok() ) {
        // TODO set temperature value, i.e., you can define it as you wish
        temp_data.data =  i;
        imu_data.x = i*0.2;
        imu_data.y = i*0.4;
        imu_data.z = i*0.2;
        // TODO set acceleration values: x, y, and z
        // TODO set desired speed 
        // TODO publish msg_temperature and msg_imu_acceleration
        temp_pub_->publish(temp_data);
        acc_pub_->publish(imu_data); 
        // TODO call the service srv_speed and if it get executed, print previous_speed and new_speed
        auto request = std::make_shared<friend_msgs::srv::SetSpeed::Request>();
        request->desired_speed = 0.45*i;
        auto future = client_get_speed_->async_send_request(request);
        RCLCPP_INFO(get_logger(), "Trying to call the /speed service for setting speed");
        // if(rclcpp::spin_until_future_complete(this->get_node_base_interface(), future) == rclcpp::FutureReturnCode::SUCCESS){
        //   RCLCPP_INFO_STREAM(get_logger(), "service respose "<< future.get()->new_speed);
        // }else{
        //   RCLCPP_ERROR(get_logger(), "Something wrong with the server");
        // }
        auto status = future.wait_for(500ms);  
        if (status == std::future_status::ready)
        {
          RCLCPP_INFO_STREAM(get_logger(), "service respose "<< future.get()->new_speed);
        }
        else
        {
          RCLCPP_ERROR(get_logger(), "Something wrong with the server");
        }

        ++i;
        rclcpp::spin_some(this->get_node_base_interface());
        rate.sleep();
      }
    }
    private:
      float previous_speed = 0.;
      float new_speed      = 0.;
      rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr temp_pub_;
      rclcpp::Publisher<geometry_msgs::msg::Vector3>::SharedPtr acc_pub_;
      rclcpp::Client<friend_msgs::srv::SetSpeed>::SharedPtr client_get_speed_;
};


int main( int argc, char **argv )
{
  rclcpp::init( argc, argv);
  auto node = std::make_shared<HagenPub>();
  node->sendMessages();
  rclcpp::spin(node);
  return EXIT_SUCCESS;
}

