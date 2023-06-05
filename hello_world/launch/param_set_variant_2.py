from launch import LaunchDescription
from launch_ros.actions import Node
import os 
from ament_index_python.packages import get_package_share_directory

def generate_launch_description():

    pkg_dir = get_package_share_directory('hello_world')
    param_file = os.path.join(pkg_dir, 'config', 'params_user_info.yaml')
    
    param_reader_cmd = Node(
        package='hello_world',
        executable='param_reader_user_info',
        parameters=[param_file],
        output='screen'
    )

    ld = LaunchDescription()
    ld.add_action(param_reader_cmd)

    return ld
