from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='ros2_tf2_mastery',
            executable='static_transform_broadcaster',
            output='screen'
        ),
        Node(
            package='ros2_tf2_mastery',
            executable='dynamic_transform_broadcaster',
            output='screen'
        ),
        Node(
            package='ros2_tf2_mastery',
            executable='transform_listener',
            output='screen'
        )
    ])
