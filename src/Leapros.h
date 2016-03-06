/*************************************************************************
	> File Name: Leapros.h
	> Author:TAI Lei 
	> Mail: 
	> Created Time: Saturday, March 05, 2016 PM09:59:00 HKT
    > This is the header which was used to change the tool orintation to the cmd_vel of ros topic to control the move of robot
 ************************************************************************/

#ifndef _LEAPROS_H
#define _LEAPROS_H

#include <ros/ros.h>
#include <Leap.h>
#include <geometry_msgs/Twist.h>


class RosListener:public Leap::Listener{
  public:
    
    //RosListener();
    virtual void onInit(const Leap::Controller& );
    virtual void onConnect(const Leap::Controller& );
    virtual void onDisconnect(const Leap::Controller& );
    virtual void onExit(const Leap::Controller& );
    virtual void onFrame(const Leap::Controller& );

  private:
    ros::NodeHandle nh_;
    ros::Publisher vel_pub;
    geometry_msgs::Twist teleop_;
};







#endif
