from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():

    joy_hagen_pub = Node(
        package='ros2_visualize',
        executable='joy_hagen_pub',
        output='screen'
    )
    
    rviz = Node(
            package='rviz2',
            namespace='',
            executable='rviz2',
            name='rviz2',
            arguments=['-d' + os.path.join(get_package_share_directory('ros2_visualize'), 'config', 'rviz_config.rviz')]
        )

    ld = LaunchDescription()
    ld.add_action(joy_hagen_pub)
    ld.add_action(rviz)

    return ld
