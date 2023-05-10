# ROS-tf2odom

This code publishes odom information using the difference between the previous tf and the current tf in a situation where tf is given at every time step (in 2D).

Ubuntu 20.04
ROS Noetic

```c
>> cd ~/catkin_ws/src
>> git clone ~
>> cd ..
>> catkin_make
>> source ./devel/setup.bash
>> rosrun tf2odom tf2odom
```

<br/> Subscribe: /tf
<br/> Publish : /odom
<br/> Unit: position[m],velocity[m/s],angular rate[rad/s]
