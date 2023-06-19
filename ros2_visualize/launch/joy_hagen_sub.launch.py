from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os 

def generate_launch_description():

    joy_hagen_sub = Node(
        package='ros2_visualize',
        executable='joy_hagen_sub',
        output='screen'
    )

    ld = LaunchDescription()
    ld.add_action(joy_hagen_sub)
    return ld