# 🧪 ROS 2 Composition & Intra-Process Communication Lab

> **Objective**: Understand and apply ROS 2 composition techniques, including static/dynamic node loading, intra-process communication (IPC), and performance profiling using large messages like PointCloud2.

---

## ✅ Main Task: Implement & Analyze Composable PointCloud Nodes


### 🧩 Task 1: Create Composable Nodes

* [ ] Create `PointCloudPublisher` component, save it as src/pointcloud_publisher.cpp

  * [ ] Publishes large fake `PointCloud2` (\~100k points) at 10 Hz
  * [ ] Adds timestamp to `header.stamp`
* [ ] Create `PointCloudSubscriber` component, save it as src/pointcloud_subscriber.cpp

  * [ ] Computes and logs latency in milliseconds
* [ ] Register both using `RCLCPP_COMPONENTS_REGISTER_NODE`

---

### 🧪 Task 2: Launch Using Composition (Static)

* [ ] Create a launch file using `ComposableNodeContainer`

  * [ ] Use `component_container_mt`
  * [ ] Load both nodes statically in the launch file
* [ ] Enable **intra-process communication**:

  ```python
  extra_arguments=[{'use_intra_process_comms': True}]
  ```

---

### 🔄 Task 3: Dynamic Component Loading (via Launch)

* [ ] Modify the launch file to use:

  * [ ] Empty container
  * [ ] `LoadComposableNodes` to dynamically load both components
  * [ ] Toggle `use_intra_process_comms` via launch arg:

    ```bash
    ros2 launch ... use_ipc:=true
    ```

---

### 📈 Task 4: Real-Time Latency Plotting

* [ ] Add `latency_plot_and_log.py` script

  * [ ] Subscribes to `/cloud`
  * [ ] Plots latency in real time (Matplotlib)
  * [ ] Logs data to `latency_log_<label>.csv`
* [ ] Run with:

  ```bash
  python3 latency_plot_and_log.py --label ipc_on
  python3 latency_plot_and_log.py --label ipc_off
  ```

---

### 📊 Task 5: Compare IPC ON vs OFF

* [ ] Run the system twice:

  * [ ] Once with `use_ipc:=true`
  * [ ] Once with `use_ipc:=false`
* [ ] Save and label both CSV logs
* [ ] Plot both logs using:

  ```bash
  python3 compare_logs.py
  ```
* [ ] Analyze:

  * [ ] Latency range and jitter
  * [ ] CPU usage via `top` or `htop`
  * [ ] Message flow in `rqt_graph`

---

## 🧠 Discussion / Reflection

* [ ] What was the average latency with and without IPC?
* [ ] Why does intra-process communication reduce latency and CPU load?
* [ ] What changes in `rqt_graph` when IPC is used?
* [ ] Would IPC work across separate processes? Why or why not?

---

### 🧰 Bonus Tasks (Optional)

* [ ] Use `PlotJuggler` or `rqt_plot` for latency visualization
* [ ] Extend publisher to publish RGB / intensity fields
* [ ] Add QoS overrides and experiment with reliability
