#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>
#include <joy_twist/joy_twist.h>


void TimerCallback(const ros::TimerEvent&)
  {
  ros::NodeHandle timer_node_hndl;

  gep_joytwist.publish(twist_msg);
    
  }

void joyCallback(const sensor_msgs::Joy::ConstPtr& msg_var)
  {

    twist_msg.angular.z = msg_var->axes[0];
    twist_msg.linear.x = msg_var->axes[1];
  
  }

int main(int argc, char ** argv){
  ros::init(argc, argv, "gep_joytwist_node");

  ros::NodeHandle node_handle;

  ros::Subscriber sub = node_handle.subscribe<sensor_msgs::Joy>("joy", 10, &joyCallback); 

  gep_joytwist = node_handle.advertise<geometry_msgs::Twist>("edumip/cmd", 10);


  //check topics and publish in callback
  ros::Timer timer = node_handle.createTimer(ros::Duration(0.1), TimerCallback);

  //block forever servicing callbacks
  ros::spin();
  
  return 0;
}
