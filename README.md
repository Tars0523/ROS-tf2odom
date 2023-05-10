# ROS-tf2odom

This code publishes odom information using the difference between the previous tf and the subsequent tf in a situation where tf is given at every time step.
```c
>> cd ~/catkin_ws/src
>> git clone ~
>> cd ..
>> catkin_make
>> source ./devel/setup.bash
>> rosrun tf2odom tf2odom
```

