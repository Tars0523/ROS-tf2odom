#include <iostream>
#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <nav_msgs/Odometry.h>
#include <tf/transform_broadcaster.h>
int main(int argc, char **argv){

  ros::init(argc, argv, "tf2odom");
  ros::NodeHandle node;
  ros::Publisher odom_pub = node.advertise<nav_msgs::Odometry>("odom",10);
  
  double current_x = 0;
  double current_y = 0;
  double before_x = 0;
  double before_y = 0;
  
  double current_z = 0;
  double current_w = 0;
  double before_z = 0 ;
  double before_w = 0;
  double current_yaw = 0;
  double before_yaw = 0;

  double x = 0;
  double y = 0;
  double th = 0;
  
  double vx = 0;
  double vy = 0;
  double vth = 0;

  double current_time =ros::Time::now().toSec();
  double before_time =ros::Time::now().toSec();
  double delta_t = 0 ;
  
  double flag = 0;

  tf::TransformListener listener;
  tf::TransformBroadcaster odom_broadcaster;


  while(node.ok())
  {
    tf::StampedTransform transform;

    try{
      
      listener.lookupTransform("/map","/scanmatcher_frame",ros::Time(0),transform);

      if (flag == 1){

        ros::Duration(0.1).sleep();
        ROS_INFO("working");

        current_time = ros::Time::now().toSec();
        current_x = transform.getOrigin().x();
        current_y = transform.getOrigin().y();

        current_z = transform.getRotation().z();
        current_w = transform.getRotation().w();
        current_yaw = atan2(2*current_z*current_w,1-2*current_z*current_z);


        delta_t = current_time-before_time;
        vx =   (current_x - before_x)/delta_t;
        vy =   (current_y - before_y)/delta_t;
        vth = (current_yaw-before_yaw)/delta_t;
        ROS_INFO("v_x:%f[m/s]",vx);
        ROS_INFO("v_y:%f[m/s]",vy);
        ROS_INFO("yaw_rates:%f[angle/s]",vth*180/3.14);
        // make odom init //
        geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(current_yaw);
        //geometry_msgs::TransformStamped odom_trans;
        //odom_trans.header.stamp = current_time;
        //odom_trans.header.frame_id = "odom";
        //odom_trans.child_frame_id = "base_link";
        //odom_trans.transform.translation.x = current_x;
        //odom_trans.transform.translation.y = current_y;
        //odom_trans.transform.translation.z = 0.0;
        //odom_trans.transform.rotation = odom_quat;
        //odom_broadcaster.sendTransform(odom_trans);
        nav_msgs::Odometry odom;
        odom.header.stamp = ros::Time::now();
        odom.header.frame_id = "odom";
        odom.pose.pose.position.x = current_x;
        odom.pose.pose.position.y = current_y;
        odom.pose.pose.position.z = 0.0;
        odom.pose.pose.orientation = odom_quat;
        odom.child_frame_id = "base_link";
        odom.twist.twist.linear.x = vx;
        odom.twist.twist.linear.y = vy;
        odom.twist.twist.angular.z = vth;
        odom_pub.publish(odom);
        // make odom end //


        before_time = current_time;
        
        before_x = current_x;
        before_y = current_y;
        
        before_z = current_z;
        before_w = current_w;
        
        before_yaw = current_yaw;
      }
      if(flag == 0){

        current_time = ros::Time::now().toSec();
        current_x = transform.getOrigin().x();
        current_y = transform.getOrigin().y();

        current_z = transform.getRotation().z();
        current_w = transform.getRotation().w();
        current_yaw = atan2(2*current_z*current_w,1-2*current_z*current_z);

        before_time = current_time;
        before_x = current_x;
        before_y = current_y;
        before_z = current_z;
        before_w = current_w;
        before_yaw = current_yaw;
        flag = 1;
        
      }
    }

    catch (tf::TransformException ex){
      ROS_ERROR("ERROR");
      ros::Duration(1).sleep();
    }
    
  }

  return 0;
}