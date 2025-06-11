from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import ComposableNodeContainer, LoadComposableNodes
from launch_ros.descriptions import ComposableNode

def generate_launch_description():
    use_ipc = LaunchConfiguration('use_ipc')

    declare_use_ipc = DeclareLaunchArgument(
        'use_ipc',
        default_value='true',
        description='Enable intra-process communication'
    )

    cloud_pub = ComposableNode(
        package='ros2_composition',
        plugin='PointCloudPublisher',
        name='pointcloud_publisher',
        extra_arguments=[{'use_intra_process_comms': use_ipc}]
    )

    cloud_sub = ComposableNode(
        package='ros2_composition',
        plugin='PointCloudSubscriber',
        name='pointcloud_subscriber',
        extra_arguments=[{'use_intra_process_comms': use_ipc}]
    )

    container = ComposableNodeContainer(
        name='cloud_container',
        namespace='',
        package='rclcpp_components',
        executable='component_container_mt',
        composable_node_descriptions=[],
        output='screen'
    )

    load_components = LoadComposableNodes(
        target_container='cloud_container',
        composable_node_descriptions=[cloud_pub, cloud_sub]
    )

    return LaunchDescription([
        declare_use_ipc,
        container,
        load_components
    ])
