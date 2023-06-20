import math 
import rclpy 
from time import sleep 
from rclpy.node import Node
from std_msgs.msg import String 
from geometry_msgs.msg import Twist     
from sensor_msgs.msg import LaserScan    
from geometry_msgs.msg import Pose 
from std_msgs.msg import Float64MultiArray
from rclpy.qos import qos_profile_sensor_data 
import numpy as np 
 
class Controller(Node):
  def __init__(self):
    super().__init__('Controller')
    self.subscription = self.create_subscription(
                        Float64MultiArray,
                        '/hagen_robot/state_est',
                        self.state_estimate_callback,
                        10)
    self.subscription 
    self.scan_subscriber = self.create_subscription(
                           LaserScan,
                           '/hagen_robot/laser/out',
                           self.scan_callback,
                           qos_profile=qos_profile_sensor_data)
    self.publisher_ = self.create_publisher(
                      Twist, 
                      '/hagen_robot/cmd_vel', 
                      10)
   
 
  def state_estimate_callback(self, msg):
    """
    Extract the position and orientation data. 
    """
    curr_state = msg.data
    self.current_x = curr_state[0]
    self.current_y = curr_state[1]
    self.current_yaw = curr_state[2]
    self.send_control()
 
  def scan_callback(self, msg):
    #  -90 degrees to 90 degrees....0 to 180 degrees)
    self.left_dist = msg.ranges[180]
    self.leftfront_dist = msg.ranges[135]
    self.front_dist = msg.ranges[90]
    self.rightfront_dist = msg.ranges[45]
    self.right_dist = msg.ranges[0]
             
  def send_control(self):
    msg = Twist()
    msg.linear.x = 0.05
    msg.linear.y = 0.05
    msg.linear.z = 0.0
    msg.angular.x = 0.0
    msg.angular.y = 0.0
    msg.angular.z = 0.05       
    self.publisher_.publish(msg)    
 
def main(args=None):
    rclpy.init(args=args)
    controller = Controller()
    rclpy.spin(controller)
    controller.destroy_node()
    rclpy.shutdown()
 
if __name__ == '__main__':
    main()