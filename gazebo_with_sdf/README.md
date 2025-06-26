### 🧱 What is SDF?

SDF (Simulation Description Format) is an XML-based format used to describe objects and environments in Gazebo. It is highly extensible and supports physical properties, visuals, sensors, and plugins.

![model_v1](https://github.com/user-attachments/assets/c3be54ce-462d-47ae-8b63-3a1909a8f5b7)

---

### 🧰 0. `<model>` – The Robot Container

The `<model>` tag defines a complete robot or simulation object. It contains links, joints, sensors, and plugins.

```xml
<model name="my_robot">
  <static>false</static>
  <!-- Add links, joints, sensors here -->
</model>
```

📝 **Attributes**:

* `name`: Unique name of the model instance.
* `static`: If `true`, the model is fixed and unaffected by physics.

A typical SDF starts with:

```xml
<?xml version="1.0"?>
<sdf version="1.6">
  <model name="example_model">
    <!-- components -->
  </model>
</sdf>
```

---

### 🔗 1. `<link>` – Defining Robot Parts

The `<link>` tag represents a rigid body in the robot. Each robot is composed of one or more links.

```xml
<link name="base_link">
  <pose>0 0 0.1 0 0 0</pose>
  <!-- Visual and collision components -->
</link>
```

📝 **Attributes**:

* `name`: Unique name for the link.
* `pose`: Position (x y z) and orientation (roll pitch yaw) relative to parent or world.

---

### 👁 2. `<visual>` – Defining Appearance

The `<visual>` tag defines how a link looks in the simulation. It can be primitive geometry or mesh.

#### 🧱 Using Primitive Geometry

```xml
<visual name="visual">
  <geometry>
    <box>
      <size>1 0.5 0.3</size>
    </box>
  </geometry>
</visual>
```

#### 🧊 Using Mesh Files

You can use mesh files like `.dae`, `.stl`, or `.obj` to represent complex shapes:

```xml
<visual name="mesh_visual">
  <geometry>
    <mesh>
      <uri>model://my_robot/meshes/robot_body.dae</uri>
      <scale>1.0 1.0 1.0</scale>
    </mesh>
  </geometry>
</visual>
```

📝 **Notes**:

* Mesh path must begin with `model://` if you're using a Gazebo model directory.
* Meshes can be scaled with the `<scale>` tag.
* Keep mesh complexity low for performance.

---

The `<visual>` tag defines how a link looks in the simulation. It can be primitive geometry or mesh.

```xml
<visual name="visual">
  <geometry>
    <box>
      <size>1 0.5 0.3</size>
    </box>
  </geometry>
</visual>
```

📝 **Note**: Visuals do not affect physics.

---

### 🛡 3. `<collision>` – Defining Physical Boundaries

The `<collision>` tag defines the shape used for physical interactions (e.g., contact, collisions).

```xml
<collision name="collision">
  <geometry>
    <box>
      <size>1 0.5 0.3</size>
    </box>
  </geometry>
</collision>
```

📝 **Note**: Collisions affect physics and should be simple shapes for better performance.

---

### 🤝 4. `<joint>` – Connecting Links

Joints are used to connect two links and allow relative movement.

```xml
<joint name="wheel_joint" type="revolute">
  <parent>base_link</parent>
  <child>wheel_link</child>
  <axis>
    <xyz>0 1 0</xyz>
  </axis>
</joint>
```

📝 **Types**: `fixed`, `revolute`, `prismatic`, `continuous`, etc.

---

### 🧲 5. `<inertial>` – Mass and Inertia Properties

This tag defines how mass is distributed in a link, important for physics.

```xml
<inertial>
  <mass>1.0</mass>
  <inertia>
    <ixx>0.1</ixx>
    <iyy>0.1</iyy>
    <izz>0.1</izz>
  </inertia>
</inertial>
```

---

### 👂 6. `<sensor>` – Simulated Sensors

Sensors simulate cameras, LIDARs, IMUs, etc.

```xml
<sensor name="laser" type="ray">
  <pose>0 0 0.1 0 0 0</pose>
  <ray>
    <scan>
      <horizontal>
        <samples>180</samples>
        <min_angle>-1.57</min_angle>
        <max_angle>1.57</max_angle>
      </horizontal>
    </scan>
    <range>
      <min>0.2</min>
      <max>10</max>
    </range>
  </ray>
</sensor>
```

---

### 🧩 7. `<plugin>` – Adding Behavior

Plugins extend robot capabilities, such as integrating with ROS, controlling wheels, publishing sensor data, or simulating control systems.

#### 🦾 Example: Differential Drive Plugin (ROS Integration)

This example configures a ROS-compatible differential drive robot:

```xml
<plugin name='diff_drive' filename='libgazebo_ros_diff_drive.so'>
  <ros>
    <namespace>/hagen_robot</namespace>
    <remapping>cmd_vel:=cmd_vel</remapping>
    <remapping>odom:=odom</remapping>
  </ros>

  <left_joint>left_wheel_hinge</left_joint>
  <right_joint>right_wheel_hinge</right_joint>

  <wheel_separation>0.26</wheel_separation>
  <wheel_diameter>0.2</wheel_diameter>

  <max_wheel_torque>20</max_wheel_torque>
  <max_wheel_acceleration>1.0</max_wheel_acceleration>

  <publish_odom>true</publish_odom>
  <publish_odom_tf>true</publish_odom_tf>
  <publish_wheel_tf>true</publish_wheel_tf>

  <odometry_frame>odom</odometry_frame>
  <robot_base_frame>chassis</robot_base_frame>
</plugin>
```

📝 **Explanation of Key Elements**:

* `<filename>`: Name of the plugin library file used by Gazebo.
* `<namespace>`: ROS namespace for topic isolation.
* `<remapping>`: Allows remapping of ROS topics.
* `<left_joint>` / `<right_joint>`: Names of the joints driving the wheels.
* `<wheel_separation>`: Distance between the wheels (meters).
* `<wheel_diameter>`: Diameter of the wheels (meters).
* `<max_wheel_torque>`: Torque limit applied to each wheel (Nm).
* `<max_wheel_acceleration>`: Maximum wheel acceleration (m/s²).
* `<publish_odom>`: If `true`, publishes `/odom` topic.
* `<publish_odom_tf>`: If `true`, publishes TF transform from `odom` to `base_link`.
* `<publish_wheel_tf>`: Publishes TFs for the wheels.
* `<odometry_frame>`: Name of the odometry reference frame.
* `<robot_base_frame>`: Base frame of the robot (typically `base_link` or `chassis`).

This plugin enables ROS-compatible motion control using `geometry_msgs/Twist` messages published to `/hagen_robot/cmd_vel`.

Plugins extend robot capabilities (e.g., ROS interfaces, control).

```xml
<plugin name="diff_drive" filename="libgazebo_ros_diff_drive.so">
  <ros>
    <namespace>/robot</namespace>
    <remapping>cmd_vel:=cmd_vel</remapping>
  </ros>
  <left_joint>left_wheel_joint</left_joint>
  <right_joint>right_wheel_joint</right_joint>
</plugin>
```

---

### 🧪 Example: A Simple Box Robot

```xml
<?xml version="1.0"?>
<sdf version="1.6">
  <model name="simple_box_robot">
    <static>false</static>
    <link name="chassis">
      <pose>0 0 0.1 0 0 0</pose>
      <collision name="collision">
        <geometry>
          <box>
            <size>1 0.5 0.3</size>
          </box>
        </geometry>
      </collision>
      <visual name="visual">
        <geometry>
          <box>
            <size>1 0.5 0.3</size>
          </box>
        </geometry>
      </visual>
    </link>
  </model>
</sdf>
```

---

### 🔩 Types of Joints in SDF

SDF supports different joint types to simulate how links move relative to each other.

#### 1. `revolute` – Rotational around an axis

```xml
<joint name="revolute_joint" type="revolute">
  <parent>link1</parent>
  <child>link2</child>
  <axis>
    <xyz>0 0 1</xyz>
  </axis>
</joint>
```

* Allows rotation around a fixed axis.
* Example: wheel attached to chassis.

#### 2. `prismatic` – Linear motion along an axis

```xml
<joint name="slide_joint" type="prismatic">
  <parent>link1</parent>
  <child>link2</child>
  <axis>
    <xyz>1 0 0</xyz>
  </axis>
</joint>
```

* Allows sliding movement.
* Example: telescopic arm or lift.

#### 3. `fixed` – No relative motion

```xml
<joint name="fixed_joint" type="fixed">
  <parent>link1</parent>
  <child>link2</child>
</joint>
```

* Links are rigidly connected.
* Example: sensor mounted on a robot.

#### 4. `continuous` – Infinite rotation

```xml
<joint name="spin_joint" type="continuous">
  <parent>link1</parent>
  <child>link2</child>
  <axis>
    <xyz>0 1 0</xyz>
  </axis>
</joint>
```

* Like revolute, but without rotation limits.
* Example: drone rotor.

#### 5. `ball` – 3-DOF rotation (no translation)

```xml
<joint name="ball_joint" type="ball">
  <parent>link1</parent>
  <child>link2</child>
</joint>
```

* Spherical joint, allows free rotation.
* Example: gimbal mount.

#### 6. `planar` – 2D movement (x, y + rotation around z)

```xml
<joint name="planar_joint" type="planar">
  <parent>link1</parent>
  <child>link2</child>
</joint>
```

* Used for 2D platforms.

---

### 🧱 Types of Links

While SDF has only one `<link>` element, links can serve different roles based on how they are used:

#### 1. **Base Link**

* First link in the model; typically connected to the world or ground.
* Example:

```xml
<link name="base_link">
  <pose>0 0 0 0 0 0</pose>
</link>
```

#### 2. **Actuated Link**

* A link connected via a joint that can move, like a wheel or arm segment.
* Example:

```xml
<link name="wheel_link">
  <!-- used with revolute joint -->
</link>
```

#### 3. **Sensor Link**

* Link that holds a sensor, usually fixed to the robot.
* Example:

```xml
<link name="laser_link">
  <sensor name="laser" type="ray">...</sensor>
</link>
```

#### 4. **Passive or Dummy Link**

* Used for spacing or visualization only; often has no collision or mass.

---

### ✅ Summary

| Component     | Purpose                                |
| ------------- | -------------------------------------- |
| `<link>`      | Rigid part of robot                    |
| `<visual>`    | Appearance                             |
| `<collision>` | Physical interactions                  |
| `<joint>`     | Connects links with movement freedom   |
| `<sensor>`    | Simulates hardware sensors             |
| `<plugin>`    | Adds behavior (ROS, controllers, etc.) |


### 🔁 **SDF Hierarchy Overview**

#### ✅ **Top-Level Structure**

```xml
<sdf>
  <model>
    <!-- siblings: link, joint, plugin, etc. -->
  </model>
</sdf>
```

---

### 📦 `<sdf>`

* **Parent of**: `<model>`
* **Sibling of**: *None (it's the root)*
* **Child**: `<model>`, `<world>`, etc.

---

### 🧰 `<model>`

* **Parent of**:

  * `<link>`
  * `<joint>`
  * `<plugin>`
  * `<pose>`
* **Child of**: `<sdf>`
* **Siblings** inside model: All other model-level tags

---

### 🔗 `<link>`

* **Parent of**:

  * `<visual>`
  * `<collision>`
  * `<inertial>`
  * `<sensor>`
* **Child of**: `<model>`
* **Siblings** inside model: other `<link>`, `<joint>`

---

### 👁 `<visual>` and 🛡 `<collision>`

* **Child of**: `<link>`
* **Siblings**: `<inertial>`, `<sensor>`

Each can have their own `<geometry>` and `<pose>`.

---

### 🤝 `<joint>`

* **Child of**: `<model>`
* **Parent of**: `<parent>`, `<child>`, `<axis>`, etc.
* Connects two `<link>`s

---

### 👂 `<sensor>`

* **Child of**: `<link>`
* **Siblings**: `<visual>`, `<collision>`, `<inertial>`
* **Can contain**: `<camera>`, `<ray>`, `<imu>`, depending on type

---

### 🧩 `<plugin>`

* **Child of**: `<model>` (can also be inside `<world>`)
* **Sibling of**: `<link>`, `<joint>`

Yes, **URDF (Unified Robot Description Format)** and **SDF (Simulation Description Format)** are different robot description formats, each with its own features and use cases.

---

### 🔧 URDF (Unified Robot Description Format)

* **Used by**: Primarily in **ROS (Robot Operating System)**.
* **Format**: XML-based.
* **Purpose**: Describes the **kinematics**, **dynamics**, and **visual/collision geometry** of robots.
* **Limitations**:

  * No support for world objects (only the robot itself).
  * Limited support for materials, sensors, and advanced physics.
* **Tools**: Supported in RViz, MoveIt, ROS Control.
* **Parser**: `urdf_parser_plugin`.

---

### 🎮 SDF (Simulation Description Format)

* **Used by**: Primarily in **Gazebo** and **Ignition Gazebo** simulators.
* **Format**: XML-based, more structured than URDF.
* **Purpose**: Describes **full simulation environments**, including robots, sensors, lights, terrain, and physics.
* **Features**:

  * Supports **plugins**, **sensors**, **actuators**, **materials**, **lighting**, and more advanced **physics** settings.
  * Supports **multiple robots** and **worlds** in a single file.
* **Tools**: Native format for Gazebo.

---

### 🔄 Conversions

* You can **convert URDF → SDF** using `gz sdf -p <robot.urdf>`.
* For better Gazebo integration, people often write **URDF + custom Gazebo tags**, or directly use SDF.

---

### Summary Table

| Feature                 | URDF                    | SDF                           |
| ----------------------- | ----------------------- | ----------------------------- |
| Primary Use             | Robot modeling in ROS   | Simulation in Gazebo/Ignition |
| Format                  | XML                     | XML (more structured)         |
| Supports Sensors        | ❌ (limited via plugins) | ✅ (native support)            |
| Supports Environments   | ❌                       | ✅                             |
| Physics Engine Settings | ❌                       | ✅                             |
| Multi-Robot Support     | ❌                       | ✅                             |
| Plugins Support         | ❌ (via `<gazebo>` tags) | ✅ (natively supported)        |


# 🎓 ROS 2 + Gazebo Simulation Tutorial

---

## 🧱 Step 1: Create a New ROS 2 Package

```bash
cd ~/ros2_ws/src
ros2 pkg create --build-type ament_cmake --dependencies rclpy gazebo_ros my_robot_sim
```

This creates a package named `my_robot_sim`.

---

## 🗃️ Step 2: Organize Your Folders

Inside the new package:

```bash
cd ~/ros2_ws/src/my_robot_sim
mkdir -p models/my_robot
mkdir -p worlds
mkdir -p launch
```

---

## 🤖 Step 3: Add Your Robot Model (SDF)

### 📄 `models/my_robot/model.sdf`

```xml
<?xml version="1.0" ?>
<sdf version="1.6">
  <model name="my_robot">
    <static>false</static>
    <link name="base_link">
      <visual name="visual">
        <geometry>
          <box><size>0.5 0.3 0.2</size></box>
        </geometry>
        <material>
          <ambient>0 1 0 1</ambient>
        </material>
      </visual>
    </link>
  </model>
</sdf>
```

### 📄 `models/my_robot/model.config`

```xml
<?xml version="1.0" ?>
<model>
  <name>My Robot</name>
  <version>1.0</version>
  <sdf>model.sdf</sdf>
  <author>
    <name>Student</name>
  </author>
</model>
```

---

## 🌍 Step 4: Add a Custom World

### 📄 `worlds/my_world.world`

```xml
<?xml version="1.0" ?>
<sdf version="1.6">
  <world name="default">
    <include>
      <uri>model://ground_plane</uri>
    </include>
    <include>
      <uri>model://sun</uri>
    </include>
  </world>
</sdf>
```

---

## 🚀 Step 5: Create the Launch File

### 📄 `launch/sim_launch.py`

```python
from launch import LaunchDescription
from launch.actions import ExecuteProcess, SetEnvironmentVariable
from launch_ros.actions import Node
import os
from ament_index_python.packages import get_package_share_directory

def generate_launch_description():
    pkg_path = get_package_share_directory('my_robot_sim')
    world_path = os.path.join(pkg_path, 'worlds', 'my_world.world')
    model_path = os.path.join(pkg_path, 'models')
    sdf_file = os.path.join(model_path, 'my_robot', 'model.sdf')

    return LaunchDescription([
        # Set GAZEBO_MODEL_PATH so Gazebo can find the robot
        SetEnvironmentVariable('GAZEBO_MODEL_PATH', model_path),

        # Start Gazebo with the custom world
        ExecuteProcess(
            cmd=['gazebo', '--verbose', world_path, '-s', 'libgazebo_ros_factory.so'],
            output='screen'
        ),

        # Spawn the robot into Gazebo
        Node(
            package='gazebo_ros',
            executable='spawn_entity.py',
            arguments=['-file', sdf_file, '-entity', 'my_robot', '-x', '0', '-y', '0', '-z', '0.1'],
            output='screen'
        )
    ])
```

---

## 🛠 Step 6: Add Dependencies

Edit your `package.xml` to include:

```xml
<exec_depend>gazebo_ros</exec_depend>
```

No changes to `CMakeLists.txt` are needed unless you're compiling C++ code.

---

## 🧪 Step 7: Build the Workspace

```bash
cd ~/ros2_ws
colcon build
source install/setup.bash
```

---

## 🟢 Step 8: Launch the Simulation

```bash
ros2 launch my_robot_sim sim_launch.py
```

This will:

* Start Gazebo with your custom world
* Load your robot model into the world
* Connect Gazebo to ROS 2

---

## 🧠 Bonus: Run Manually via Command Line

### 1. Export model path

```bash
export GAZEBO_MODEL_PATH=$GAZEBO_MODEL_PATH:$HOME/ros2_ws/src/my_robot_sim/models
```

### 2. Run the world:

```bash
gazebo ~/ros2_ws/src/my_robot_sim/worlds/my_world.world -s libgazebo_ros_factory.so
```

### 3. In another terminal, spawn the robot:

```bash
ros2 run gazebo_ros spawn_entity.py \
  -file $GAZEBO_MODEL_PATH/my_robot/model.sdf \
  -entity my_robot \
  -x 0 -y 0 -z 0.1
```

---

## 🧾 Final Folder Structure

```
my_robot_sim/
├── models/
│   └── my_robot/
│       ├── model.sdf
│       └── model.config
├── worlds/
│   └── my_world.world
├── launch/
│   └── sim_launch.py
├── package.xml
├── CMakeLists.txt
```

---
