from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():

    joy_hagen_basic_control = Node(
        package='ros2_visualize',
        executable='joy_hagen_basic_control',
        output='screen'
    )
    
    rviz = Node(
            package='rviz2',
            namespace='',
            executable='rviz2',
            name='rviz2',
            arguments=['-d' + os.path.join(get_package_share_directory('ros2_visualize'), 'config', 'rviz_config.rviz')]
        )
    
    static_trans = Node(package = "tf2_ros", executable = "static_transform_publisher",
                       arguments =  ["0", "0", "2.5", "0", "0", "0", "map", "base_link"])

    ld = LaunchDescription()
    ld.add_action(joy_hagen_basic_control)
    ld.add_action(rviz)
    ld.add_action(static_trans)

    return ld

