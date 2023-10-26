# Introduction to ROS2
## Course Structure :space_invader:
    
- Section 1 :alien:	
    - ROS2 Fundamentals [:books: lec01 ](lectures/ros2_fundamentals.pdf) [:books: lec02 ](lectures/ros2_fundamentals_2.pdf) [:scroll: code](hello_world/src/)
    - Workout Examples  [:books:](lectures/recap.pdf) [:scroll: code]()
- Section 2 :alien:	
    - ROS2 Visualization  [:books:](lectures/ros2_visualization.pdf) [:scroll: code](ros2_visualize/)
    - ROS2 Debugging [:books:](lectures/ros2_debugging_and_logging.pdf) [:scroll: code](ros2_debug_logging/)	
    - ROS2 Basic Control [:scroll: code](ros2_visualize/src/joy_hagen_basic_control_todo.cpp)	
    - ROS2 Simulation (Gazebo+SDF) [:books:](lectures/ros2_gazebo_sdf.pdf) [:scroll: code](hagen_robot/hagen_robot_diff_drive/hagen_robot_diff_drive/)	
    - ROS2 Control robot [:scroll: code](hagen_robot/hagen_robot_controller/)	
- Section 3 :alien:	
    - Mini Group Project
- Section 4 👽
    - ROS2 Navigation [:books:](lectures/ros2_nav2.pdf)
- References
    - https://docs.ros.org/en/humble/index.html

## Instruction for running the docker container  

### To create a docker container (name ros_intro_node)
    cd intro_ros2/docker_image/
    docker compose up --build  
### To enter the container 
    ./server.sh enter 
