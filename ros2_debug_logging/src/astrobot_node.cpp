// astrobot_node.cpp

#include <rclcpp/rclcpp.hpp>
#include "ros2_debug_logging/helpers.hpp"

using namespace std::chrono_literals;

class AstroLoggerNode : public rclcpp::Node {
public:
  AstroLoggerNode() : Node("astro_logger_node"), cycle_count_(0) {
   
    main_timer_ = this->create_wall_timer(500ms, std::bind(&AstroLoggerNode::on_main_timer, this));
    orbiter_timer_ = this->create_wall_timer(2s, std::bind(&AstroLoggerNode::on_orbiter_ping, this));
    mode_timer_ = this->create_wall_timer(15s, std::bind(&AstroLoggerNode::on_emergency_mode, this));
  }

private:
    void on_main_timer() {
        cycle_count_++;
    }

    void on_orbiter_ping() {
    
    }

    void on_emergency_mode() {
  
    }

    std::string compute_phase() {
        if (cycle_count_ < 5) return "INIT";
        if (cycle_count_ < 15) return "RUNNING";
        return "SATURATED";
    }

    bool should_debug_power() const {
        return cycle_count_ % 4 == 0;
    }

    rclcpp::TimerBase::SharedPtr main_timer_;
    rclcpp::TimerBase::SharedPtr orbiter_timer_;
    rclcpp::TimerBase::SharedPtr mode_timer_;
    int cycle_count_;
};

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<AstroLoggerNode>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
