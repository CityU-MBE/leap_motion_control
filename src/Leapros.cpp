/*************************************************************************
	> File Name: tool_control.cpp
	> Author: 
	> Mail: 
	> Created Time: Saturday, March 05, 2016 PM09:58:25 HKT
 ************************************************************************/

#include<iostream>
#include<algorithm>
#include"Leapros.h"

//RosListener::RosListener(){
//    teleop_.linear.x=1;    
//};

void RosListener::onInit(const Leap::Controller& controller){
    std::cout << "Initialized" <<std::endl;
    vel_pub = nh_.advertise<geometry_msgs::Twist>("/cmd_vel",1);
    teleop_.linear.x = 0;
    teleop_.linear.y = 0;
    teleop_.linear.z = 0;
    teleop_.angular.x = 0;
    teleop_.angular.y = 0;
    teleop_.angular.z = 0;
}

void RosListener::onConnect(const Leap::Controller& controller){
    std::cout<< "Connected" <<std::endl;
    controller.enableGesture(Leap::Gesture::TYPE_CIRCLE);
}

void RosListener::onDisconnect(const Leap::Controller& controller){
    std::cout<< "Disconnected" <<std::endl;
}

void RosListener::onExit(const Leap::Controller& controller){
    std::cout<< "Exited" <<std::endl;
}

void RosListener::onFrame(const Leap::Controller& controller){
    const Leap::Frame frame = controller.frame();
    std::cout<<"tools: "<<frame.tools().count()<<std::endl;
   
    const Leap::ToolList tools= frame.tools();
    const Leap::Tool tool = *tools.begin();
    if (tool.id() != -1){
        std::cout<<"Tool, id: "<< tool.id() <<std::endl;
        std::cout<<"Tool position: "<<tool.tipPosition()
             <<", direction: "<<tool.direction()[0] << std::endl;
        float x_speed = tool.direction()[1];
        float z_rspeed = tool.direction()[0];
        
        // linear speed
        if (x_speed > 0.3){teleop_.linear.x = std::min(x_speed * 0.5, 0.3);}
        else if (x_speed < -0.3){teleop_.linear.x = std::max(x_speed * 0.5, -0.3);}
        else{teleop_.linear.x = 0;}
        
        //angular speed
        if (z_rspeed > 0.25 || z_rspeed < -0.25){teleop_.angular.z = z_rspeed;}
        else{teleop_.angular.z = 0;}
        
        vel_pub.publish(teleop_); 
    }else{
        teleop_.linear.x = 0;
        teleop_.angular.z = 0;
        vel_pub.publish(teleop_);
    }
}
