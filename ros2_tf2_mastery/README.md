# 🧪 ROS 2 TF Lab — Static & Dynamic Transforms, Chaining, Homogeneous Matrices, and C++ Implementation

## 🔹🚀 Objectives

This lab provides hands-on experience with essential concepts in ROS 2 TF2, including:

* ✅ Manually creating homogeneous transforms
* ✅ Using `TransformBroadcaster` for dynamic transforms
* ✅ Using `StaticTransformBroadcaster` for static transforms
* ✅ Composing and chaining transforms
* ✅ Observing the effect of transform order (non-commutativity)
* ✅ Converting between quaternion and roll-pitch-yaw representations
* ✅ Using `tf2::BufferCore` and `TransformListener` for runtime lookup
* ✅ Representing transforms using `Eigen::Affine3d` and 4×4 matrices

---

## 🔹🏹 Final Scenario Overview

Imagine a mobile robot equipped with a manipulator arm and a camera mounted at its wrist. The key frames involved are:

* `world`: Global inertial frame
* `base_link`: Mobile base of the robot
* `arm_base`: Fixed base of the arm
* `wrist`: End of the arm
* `camera`: Camera mounted on the wrist

---

A diagram showing a **(illustrative)** transformation tree connecting the frames you've described: `world`, `base_link`, `arm_base`, `wrist`, and `camera`.

```
               world
                 |
         [T_world_base_link]
                 |
             base_link
                 |
        [T_base_link_arm_base]
                 |
             arm_base
                 |
        [T_arm_base_wrist]
                 |
               wrist
                 |
        [T_wrist_camera]
                 |
              camera
```

### Description of Each Frame:

* **world**: The global/inertial reference frame.
* **base\_link**: The mobile base of the robot (e.g., wheeled platform).
* **arm\_base**: Where the manipulator is mounted on the robot's base.
* **wrist**: The last link or flange of the manipulator arm (before the tool/camera).
* **camera**: The frame for a camera rigidly mounted on the wrist.

### Sample Transform Values:

These are arbitrary just for visualization/testing purposes:

| Parent → Child         | Translation (x, y, z) \[m] | Rotation (r, p, y) \[deg] |
| ---------------------- | -------------------------- | ------------------------- |
| world → base\_link     | (1.0, 2.0, 0.0)            | (0, 0, 90)                |
| base\_link → arm\_base | (0.0, 0.0, 0.5)            | (0, 0, 0)                 |
| arm\_base → wrist      | (0.5, 0.0, 0.5)            | (0, 45, 0)                |
| wrist → camera         | (0.1, 0.0, 0.1)            | (0, 0, 0)                 |

---

## 🔹📝 Tasks Breakdown

### 1️⃣ Define Static Transforms

Implement a node that uses `StaticTransformBroadcaster` to publish:

* `base_link → arm_base`: A static **pure translation**
* `wrist → camera`: A static transform with **rotation (quaternion)** and **translation**

---

### 2️⃣ Broadcast a Dynamic Transform

Create a `TransformBroadcaster` node to simulate a rotating wrist:

* Rotate `wrist` about Z-axis relative to `base_link`
* Update the transform at **10 Hz**
* Use `sin()` and `cos()` to compute the changing quaternion

---

### 3️⃣ Chain Transforms with a Listener

Use a `TransformListener` to compute:

* `camera → base_link` by chaining:

  * `camera → wrist`
  * `wrist → base_link`

* Validate by computing:

```cpp
Transform base_to_wrist;
Transform wrist_to_camera;
Transform base_to_camera = base_to_wrist * wrist_to_camera;
```

---

### 4️⃣ Experiment: Transform Order Matters

* Reverse the transform multiplication order
* Observe and report how the resulting frame is incorrect
* Emphasize the **non-commutativity** of transforms

---

### 5️⃣ Conversion Between Representations

* Use `tf2::fromMsg()` and `tf2::toMsg()` for conversion:

  * Between `geometry_msgs::TransformStamped` and `tf2::Transform`
* Perform arithmetic using tf2 classes

---

### 6️⃣ Bonus: Homogeneous Transformation

* Use `Eigen::Affine3d` or:

```cpp
tf2::Transform::getBasis()
tf2::Transform::getOrigin()
```

* Manually form and multiply 4×4 transformation matrices
* Validate transformation chaining with matrices

---

### 7️⃣ (Optional) Use Roll-Pitch-Yaw

Instead of quaternions, construct transforms using RPY:

```cpp
tf2::Quaternion q;
q.setRPY(roll, pitch, yaw);
```

* Publish and visualize to see the effect of different rotation orders

---

