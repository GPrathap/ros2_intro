#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/bool.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <algorithm>

using std::placeholders::_1; 
using namespace std::chrono_literals;

class Commander : public rclcpp::Node {
    public:
        Commander(double delta_t): Node("commander"){

            std::vector<std::string> topic_names = {"/turtle1_cmd", "/turtle2_cmd", "/turtle3_cmd", "/turtle4_cmd"};
            std::vector<std::string> turtles_done = {"/turtle1_done", "/turtle2_done", "/turtle3_done", "/turtle4_done"};
            dones = {false, false, false, false};

            auto topic = topic_names.begin();
            auto is_done = turtles_done.begin();
            while(topic != topic_names.end()){
                turtles_pub.push_back(create_publisher<geometry_msgs::msg::Twist>(*topic, 10));
                turtles_is_done_pub.push_back(create_publisher<std_msgs::msg::Bool>(*is_done, 10));
                topic++;
                is_done++;
            }

            start_flag_sub = create_subscription<std_msgs::msg::Bool>("/start_topic", 1, 
                                std::bind(&Commander::startCallbackSub, this, _1));
            dt = delta_t;
        }

        void startCallbackSub(const std_msgs::msg::Bool::SharedPtr msg){
            start_flag = msg->data;
        }

        template<int turtle_num>
        void turtleTraj(float t){
            geometry_msgs::msg::Twist msg;
            msg.linear.x = 0;
            msg.linear.y = 0;
            msg.linear.z = 0;
            msg.angular.x = 0;
            msg.angular.y = 0;
            msg.angular.z = 1;
            if(t >= 5){
                msg.angular.z = 0;
                dones[turtle_num-1] = true;
            }
            turtles_pub[turtle_num-1]->publish(msg);
        }

        void publishDone(int i){
            std_msgs::msg::Bool msg;
            msg.data = dones[i];
            turtles_is_done_pub[i]->publish(msg);
        }

        bool start_flag = false;
        float dt = 1;
    private:
        const int TURTLE_COUNT = 4;
        std::vector<bool> dones;
        std::vector<rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr> turtles_is_done_pub;
        std::vector<rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr> turtles_pub;
        rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr start_flag_sub;
};


int main(int argc, char **argv){

    rclcpp::init(argc, argv);
    double delta_t = 0.5;
    double sim_time = 0;
    auto node = std::make_shared<Commander>(delta_t);
    rclcpp::Rate loop_rate(1s);
    while(rclcpp::ok()){
        if(node->start_flag){
            sim_time += delta_t;
            node->turtleTraj<1>(sim_time);
            node->turtleTraj<2>(sim_time);
            node->turtleTraj<3>(sim_time);
            node->turtleTraj<4>(sim_time);
        }
        for(int i = 0; i < 4; i++){
            node->publishDone(i);
        }
        rclcpp::spin_some(node);
        loop_rate.sleep();
    }
    rclcpp::shutdown();
    return 0;
}
