from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():

    container = Node(
            name='logging_basic',
            namespace='',
            package='ros2_debug_logging',
            executable='logging_basic',
            output='screen',
    )
    
    ld = LaunchDescription()
    ld.add_action(container)
    return ld