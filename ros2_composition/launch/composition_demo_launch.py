
import launch
from launch_ros.actions import ComposableNodeContainer
from launch_ros.descriptions import ComposableNode


def generate_launch_description():
        """Generate launch description with multiple components."""
        container = ComposableNodeContainer(
            name='components_executor',
            namespace='',
            package='rclcpp_components',
            executable='component_container',
            composable_node_descriptions=[
                ComposableNode(
                        package='ros2_composition',
                        plugin='composition::SenderNode',
                        name='SenderNode'),
                ComposableNode(
                        package='ros2_composition',
                        plugin='composition::ReceiverNode',
                        name='receiver_node'),
                ComposableNode(
                        package='ros2_composition',
                        plugin='composition::Server',
                        name='service_server'),
                ComposableNode(
                        package='ros2_composition',
                        plugin='composition::Client',
                        name='service_client')
            ],
            output='screen',)

        return launch.LaunchDescription([container])
