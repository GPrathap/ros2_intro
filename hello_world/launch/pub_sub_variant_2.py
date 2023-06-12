from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():

    # TODO First create a LaunchDescription() and then add 
    # publisher_node and subscriber_node 
    # Finally, return the LaunchDescription you created
    
    pub_cmd = Node(
        package='hello_world',
        executable='publisher_class_node',
        output='screen'
    )
    
    sub_cmd = Node(
        package='hello_world',
        executable='subscriber_node',
        output='screen'
    )

    ld = LaunchDescription()
    ld.add_action(pub_cmd)
    ld.add_action(sub_cmd)

    return ld 
    
    return 