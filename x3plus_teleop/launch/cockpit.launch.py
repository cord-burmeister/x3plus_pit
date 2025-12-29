from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node

import os
from ament_index_python.packages import get_package_share_directory

def generate_launch_description():

    # Include joystick_xbox launch
    joystick_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(get_package_share_directory('x3plus_teleop'), 'launch', 'joystick_xbox.launch.py')
        )
    )

    # Battery to float node
    battery_node = Node(
        package='x3plus_convert2ui',
        executable='battery_to_float_node'
    )

    # Twist to twist stamped node
    twist_stamped_node = Node(
        package='x3plus_convert2ui',
        executable='twist_to_twist_stamped_node'
    )

    # Rviz
    rviz_config = os.path.join(get_package_share_directory('x3plus_teleop'), 'config', 'cockpit.rviz')
    rviz_node = Node(
        package='rviz2',
        executable='rviz2',
        arguments=['-d', rviz_config]
    )

    return LaunchDescription([
        joystick_launch,
        battery_node,
        twist_stamped_node,
        rviz_node
    ])