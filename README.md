# x3plus_pit

This is a repository for teleoperation
cockpit packages for the robot project

## Prerequisites

* Installed ROS 2 humble distribution
* Installed robot project X3plus either as simulation or real robot

## Manual Installation

First install required development tools

``` bash
sudo apt install python3-vcstool python3-colcon-common-extensions git wget
```

Then create a new workspace and load the git repositories which are required.

``` bash
mkdir -p ~/x3plus_ws/src
cd ~/x3plus_ws/src
wget -O x3plus_pit.repos https://raw.githubusercontent.com/cord-burmeister/x3plus_pit/main/x3plus_pit.repos
vcs import < x3plus_pit.repos
```

### Install dependencies

``` bash
cd ~/x3plus_ws
source /opt/ros/$ROS_DISTRO/setup.bash
sudo rosdep init
rosdep update
rosdep install --from-paths src --ignore-src -r -i -y --rosdistro $ROS_DISTRO
```

### Build the project

``` bash
colcon build 
```

### Source the workspace

``` bash
. ~/x3plus_ws/install/setup.sh
```

## Starting commands

Start the robot as simulation or on the real hardware first.

### Starting keyboard teleoperation

One of the first possibilities to control a definitions of a robot is to operate it remotely with a teleoperation. There is a package which converts console input into twist messages. Note that the command with the default topic will be mapped to the robot topic.

``` bash
ros2 run  teleop_twist_keyboard teleop_twist_keyboard 
```

### Starting tele-operation with X-Box One S pad

``` bash
ros2 launch x3plus_teleop joystick_xbox.launch.py 
```

### Starting the cockpit

You can run it with

``` bash
ros2 launch x3plus_teleop cockpit.launch.py.
```

## Packages

| Name | Description |
| ---- | ----------- |
| x3plus_teleop | This is an ROS package which contains teleoperation functionalities for controller hardware |
| x3plus_convert2ui | This is an ROS package which contains conversion functionalities for UI elements like battery state conversion |

## Github Pages

The web site of the project can be found under

[Github Pages](https://cord-burmeister.github.io/x3plus_docs/)
