#include <memory>

#include "composition/hello_world_pub_component.hpp"
#include "composition/hello_world_sub_component.hpp"
#include "composition/hello_world_service_server.hpp"
#include "composition/hello_world_service_client.hpp"
#include "rclcpp/rclcpp.hpp"



int main(int argc, char * argv[])
{
  // Force flush of the stdout buffer.
  setvbuf(stdout, NULL, _IONBF, BUFSIZ);
  rclcpp::init(argc, argv);

  // Create an executor
  rclcpp::executors::SingleThreadedExecutor exec;
  rclcpp::NodeOptions options;


  auto pub_component = std::make_shared<composition::SenderNode>(options);
  exec.add_node(pub_component);
  auto sub_component = std::make_shared<composition::ReceiverNode>(options);
  exec.add_node(sub_component);
  auto server = std::make_shared<composition::Server>(options);
  exec.add_node(server);
  auto client = std::make_shared<composition::Client>(options);
  exec.add_node(client);
  exec.spin();

  rclcpp::shutdown();

  return 0;
}
