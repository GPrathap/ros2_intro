
---

# 🧪 ROS 2 Lab: **“Mission Control: Debugging the Astrobot”**

---

## 🪐 **Story Introduction**

 You are a systems engineer** on the **Astrobot Control Team** for **LunaRover-7**, a robotic assistant deployed on the Moon’s south pole. The robot has started **misbehaving** — skipping tasks, missing cycles, and returning invalid sensor readings.

You’ve been assigned to **instrument its ROS 2 software using advanced logging**, track down the bugs, and **get it back online safely** — before the next lunar eclipse cuts off power.
---

## 🎯 Mission Objectives

* Build a complex logger node (`AstroLoggerNode`) that can analyze robot performance
* Use conditional and throttled logging to reduce log noise
* Log events inside and outside of node classes
* Switch logging levels dynamically as the mission escalates
* Persist logs for post-mortem analysis from Earth Control

---

## 🌕 Phase 1: Boot Sequence Logging

Create a class `AstroLoggerNode`.

* On startup, log boot diagnostics:

  ```cpp
  RCLCPP_INFO(get_logger(), "[BOOT] Astrobot diagnostics initialized");
  ```
* Use `RCLCPP_WARN_STREAM_ONCE` to simulate a boot warning:

  ```cpp
  RCLCPP_WARN_STREAM_ONCE(get_logger(), "[BOOT] Gyroscope self-test failed once");
  ```

🔧 *Use a timer to simulate “heartbeat” logging every 500ms.*

---

## 🛰️ Phase 2: Orbit Mode — External Monitoring

The lunar orbiter sends periodic updates to Astrobot via a background thread.

* In `helpers.cpp`, define:

```cpp
void log_orbiter_ping(int ping_id);
```

Inside it:

```cpp
RCLCPP_INFO(rclcpp::get_logger("orbiter"), "[PING] Received from orbiter: ID = %d", ping_id);
```

* Log every 2 seconds in a node timer using `log_orbiter_ping`.

🚨 *Set orbiter log level to DEBUG to receive more telemetry.*

---

## 🌑 Phase 3: Lunar Drift Detection

The robot is drifting off course!

* Add a counter (`cycle_count_`) to simulate time steps

* Every cycle, compute `drift = (cycle_count_ % 7) * 3.5`

* Add:

```cpp
RCLCPP_WARN_STREAM_THROTTLE(get_logger(), *get_clock(), 2000,
  "[DRIFT] Position drift detected: " << drift << " mm");
```

🧠 *Throttle prevents flooding mission logs.*

---

## 🧠 Phase 4: Debugging with Logic

Something subtle is wrong with power balance.

* Implement:

```cpp
bool should_debug_power() {
  return (cycle_count_ % 4 == 0);  // Only every 4th cycle
}
```

Then log:

```cpp
RCLCPP_DEBUG_FUNCTION(get_logger(), std::bind(&AstroLoggerNode::should_debug_power, this),
  "[DEBUG] Power check triggered");
```

🔍 *These only appear when the power condition is true AND level is DEBUG.*

---

## 🌘 Phase 5: Emergency Mode Escalation

At 15 seconds into mission, simulate a mode change:

```cpp
one_shot_timer_ = this->create_wall_timer(15s, [this]() {
  RCLCPP_FATAL(get_logger(), "[ALERT] Switching to EMERGENCY_MODE");
  rcutils_logging_set_logger_level(get_logger().get_name(), RCUTILS_LOG_SEVERITY_DEBUG);
});
```

🚨 *This unlocks all suppressed debug logs going forward.*

---

## 🌐 Phase 6: Persist Logs for Earth Review

Launch the node with:

```bash
ROS_LOG_DIR=/tmp/astro_logs ROS_LOG_LEVEL=DEBUG ros2 run ros2_debug_logging astrobot_node
```

After mission ends:

```bash
grep "[DRIFT]" /tmp/astro_logs/*
```

🎯 *Review the exact times and severity of the drift issues.*

---

## 📦 Suggested File Structure

```
ros2_debug_logging/
├── src/
│   ├── astrobot_node.cpp          # Main logger node
│   ├── helpers.cpp                # External logs from orbiter, etc.
├── include/ros2_debug_logging/helpers.hpp
├── CMakeLists.txt
├── package.xml
```

---

## 🎓 Mission Debrief: Reflection Questions

* How did throttled logs help manage log size and readability?
* Why might `DEBUG_FUNCTION` be used in power-saving code paths?
* When should you prefer `*_ONCE` over `*_THROTTLE`?
* How does separating logger names improve modularity?

---

## 🧩 Bonus Challenge (Hard Mode)

💥 Simulate a **memory overflow** event every 13th cycle and conditionally log a `FATAL` with a custom recovery suggestion.

```cpp
if (cycle_count_ % 13 == 0) {
  RCLCPP_FATAL_STREAM(get_logger(), "[CRASH] Memory overflow detected! Cycle: "
                     << cycle_count_ << " — Suggest reboot sequence.");
}
```