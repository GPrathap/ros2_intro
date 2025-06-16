
## 🧪 ROS 2 Visualization Lab (C++)
### 🧭 Background Story:

You're on Mars, and *Rover-X*, your exploration robot, is mapping unknown terrain. As the lead robotics engineer, your mission is to monitor its progress in real-time using ROS 2 and RViz2. You’ll start by visualizing simple status indicators, and gradually build up to full sensor visualizations — markers, trajectories, point clouds, IMU and odometry streams.

![tryr2d2](https://github.com/user-attachments/assets/28fb353a-7e11-496f-bb28-c8d38bb955fb)

## 🔧 Setup
* ROS 2 Humble
* `rviz2`
* `rclcpp`, `visualization_msgs`, `geometry_msgs`, 

## 🧩 Part 1: Markers — "Rover Status Beacon"

### 🎯 Goal:

Show a visual cue of Rover-X's current status: blue when idle, green when exploring, red if an obstacle is detected.

### Key Concepts:

* `visualization_msgs::msg::Marker`
* Types: SPHERE, CUBE, ARROW, TEXT\_VIEW\_FACING

### C++ Node: `joy_hagen_lab_task.cpp`

* Publishes a marker at fixed pose
* Changes color/status every 2 seconds (simulate state changes)

---

## 🧩 Part 2: Marker Array — "Mapping Discovered Rock Samples"

### 🎯 Goal:

Rover-X scans rock samples and drops virtual flags (markers) on each.

### Key Concepts:

* `visualization_msgs::msg::MarkerArray`
* Unique `id` and `ns` per marker
* Add/Delete markers dynamically

### C++ Node: `joy_hagen_lab_task.cpp`

* Publishes markers at random nearby positions
* Marker type: CUBE or CYLINDER
* Includes lifetime


## 🧩 Part 3: PointCloud2 — "LiDAR Scan of Martian Terrain"

### 🎯 Goal:

Simulate a 2D LiDAR scan visualized in RViz.

### Key Concepts:

* `sensor_msgs::msg::PointCloud2`
* Custom 2D scan generated using `pcl::PointCloud<pcl::PointXYZ>`

### C++ Node: `joy_hagen_lab_task.cpp`

* Publishes a circular scan with varying intensity (simulating elevation/reflectivity)
* Use `pcl_conversions` to convert to `PointCloud2`


## 🧩 Part 4: Odometry — "Track Rover-X’s Journey"

### 🎯 Goal:

Show the rover's trajectory using odometry messages.

### Key Concepts:

* `nav_msgs::msg::Odometry`
* Pose + twist info
* Use `tf2_ros::TransformBroadcaster` for proper RViz tracking

### C++ Node: `joy_hagen_lab_task.cpp`

* Simulate a moving rover
* Broadcast transform `/odom → /base_link`


## 🧩 Part 5: IMU — "Feel the Rover’s Tilt"

### 🎯 Goal:

Visualize IMU orientation in RViz (e.g., simulate bump on rocky terrain)

### Key Concepts:

* `sensor_msgs::msg::Imu`
* Orientation + angular velocity + linear acceleration

### C++ Node: `joy_hagen_lab_task.cpp`

* Simulate pitch/roll/yaw change over time

## 📸 RViz2 Configuration

Load a pre-configured RViz2 config with:

* Marker and MarkerArray displays
* Odometry
* PointCloud2
* IMU
* TF visualization

## 🚀 Final Output

You’ll be able to:

* See status beacon change color
* Track rock samples placed
* Visualize point cloud scans
* Watch Rover-X move and rotate
* See IMU orientation updates
* Observe all transforms in TF tree
