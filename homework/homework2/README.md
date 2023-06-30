# Homework2


## Deadline

**30.06.2023, 11:59pm**


## Description
The assignment is individual. 

**Please note, there will be no tolerance for cheating.**

### Find & Fix (10 points)

You have a package called "buggy", if you try to build this package, it will give errors. Your task is to find and fix these bugs and fix them if you don't mind. The bugs and errors are not only syntax errors, or missing lines, but can be mistakes in C++ codes, msg, srv, launch file, CMakeLists and package.xml. However, the logic of the code is correct.

You may use the debugging tools to find the bugs.

Before you build your project delete `intro_ros2/homework/homework2/COLCON_IGNORE file`. Having COLCON_IGNORE file in a directory, colcon build does not build packages within the subfolders 

Your goal is to fix the errors and run ```clocon build  --packages-select buggy``` and returns you a successful build. Then, you need to run ```source install/setup.bash```. 

Then, if you fixed the errors correctly, you should run ```ros2 launch buggy test.launch.py``` and run in another terminal

```
ros2 service call /turnon "flag:            
  data: True"
```
  
Then, it should print "You finished, congrats on 10 points"

## Submission

You need to submit a single zip file that contains the following:

* zip the package after you fix it with Readme 


## Grading

* This homework costs 10 points


