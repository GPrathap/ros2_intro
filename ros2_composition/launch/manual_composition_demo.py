
import launch
from launch_ros.actions import ComposableNodeContainer
from launch_ros.descriptions import ComposableNode

def generate_launch_description():
    """Generate launch description with multiple components."""
    container = ComposableNodeContainer(
            name='components_executor',
            namespace='',
            package='ros2_composition',
            executable='manual_composition',
            output='screen',
    )

    return launch.LaunchDescription([container])
