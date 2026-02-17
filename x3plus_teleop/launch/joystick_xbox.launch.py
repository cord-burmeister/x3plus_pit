from launch import LaunchDescription
from launch_ros.actions import Node

import os
from ament_index_python.packages import get_package_share_directory

def generate_launch_description():

    joy_params = os.path.join(get_package_share_directory('x3plus_teleop'),'config','joystick_xbox.yaml')

    joy_node = Node(
            package='joy',
            executable='joy_node',
            parameters=[joy_params],
         )
    pl_node = Node(
            package='x3plus_convert2ui',
            executable='joy_to_angles_node',
            name='joy_to_angles_node',
    )
    teleop_node = Node(
            package='teleop_twist_joy', 
            executable='teleop_node',
            name = 'teleop_node',
            parameters=[joy_params],
            remappings=[('/cmd_vel', '/cmd_vel')]
            )

    return LaunchDescription([
        joy_node,
        pl_node,
        teleop_node       
    ])
