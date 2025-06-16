from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os

# https://navigation.ros.org/tutorials/docs/get_backtrace.html#from-a-launch-file

def generate_launch_description():

    joy_hagen_point_cloud = Node(
        package='ros2_visualize',
        executable='joy_hagen_point_cloud',
        # prefix=['valgrind --tool=callgrind --dump-instr=yes -v --instr-atstart=no'],
        # prefix=['xterm -e gdb -ex run --args'],
        output='screen' 
    )
    
    rviz = Node(
            package='rviz2',
            namespace='',
            executable='rviz2',
            name='rviz2',
            arguments=['-d' + os.path.join(get_package_share_directory('ros2_visualize'), 'config', 'rviz_config.rviz')]
    ) 
    
    static_trans1 = Node(package = "tf2_ros", executable = "static_transform_publisher",
                       arguments =  ["0", "0", "2.5", "0", "0", "0", "pc_frame", "marker_frame"])
    
    static_trans2 = Node(package = "tf2_ros", executable = "static_transform_publisher",
                       arguments =  ["0", "0", "2.5", "0", "0", "0", "pc_frame", "odom"])


    ld = LaunchDescription()
    ld.add_action(joy_hagen_point_cloud)
    ld.add_action(rviz)
    ld.add_action(static_trans1)
    ld.add_action(static_trans2)

    return ld
