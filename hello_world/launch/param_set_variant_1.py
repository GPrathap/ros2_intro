from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():

    param_reader_cmd = Node(
        package='hello_world',
        executable='param_reader_user_info',
        parameters=[{
            'user_name': 'r2d2',
            'user_id' : 345,
            'friends_names': ['r2d23', 'rdse4'],
            'friends_ids': [345, 6789]
        }],
        remappings=[
            ('/robot1/pose', '/turtle1/pose'),
        ],
        output='screen'
    )

    ld = LaunchDescription()
    ld.add_action(param_reader_cmd)

    return ld
