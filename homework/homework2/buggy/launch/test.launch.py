from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():

    pup = Node(
            name='up',
            namespace='',
            package='buggy',
            executable='pup',
            output='screen',
    )
    
    cub = Node(
            name='up',
            namespace='',
            package='buggy',
            executable='cub',
            output='screen',
    )
    
    ld = LaunchDescription()
    ld.add_action(pup)
    ld.add_action(cub)
    return ld