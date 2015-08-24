#include "ros/ros.h"
#include "std_msgs/String.h"
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/LaserScan.h>

#include <sstream>
#include <stdlib.h>
#include <node_defs/possum.h>

Possum::Possum(ros::NodeHandle &n)
{
	//setting base attribute defaults
	this->pose.theta = M_PI/2.0;
	this->pose.px = -12.25;
	this->pose.py = 33.5;
	this->speed.linear_x = 0.0;
	this->speed.max_linear_x = 3.0;
	this->speed.angular_z = 0.0;
	this->orientation.currently_turning = false;

	this->sub_list.node_stage_pub = n.advertise<geometry_msgs::Twist>("cmd_vel",1000);
	this->sub_list.sub_odom = n.subscribe<nav_msgs::Odometry>("base_pose_ground_truth",1000, &Possum::odom_callback, this);
	this->sub_list.sub_laser = n.subscribe<sensor_msgs::LaserScan>("base_scan",1000,&Possum::laser_callback, this);

	geometry_msgs::Point point;

	this->state = IDLE;

	row = 1; //starting at vine 1
	direction = EAST;

	point.x = this->pose.px;
	point.y = this->pose.py - (this->speed.linear_x/10.0);
	for (int i = 0; i<7; i++){
		point.x = point.x + 3.5;
		action_queue.push(point);
	}

}

void Possum::odom_callback(nav_msgs::Odometry msg)
{
	//This is the call back function to process odometry messages coming from Stage. 	
	this->pose.px = msg.pose.pose.position.x;
	this->pose.py = msg.pose.pose.position.y;

	this->orientation.rotx = msg.pose.pose.orientation.x;
	this->orientation.roty = msg.pose.pose.orientation.y;
	this->orientation.rotz = msg.pose.pose.orientation.z;
	this->orientation.rotw = msg.pose.pose.orientation.w;

	ROS_INFO("/position/x/%f", this->pose.px);
	ROS_INFO("/position/y/%f", this->pose.py);
	ROS_INFO("/status/%s/./", enum_to_string(this->state));

	calculateOrientation();
	doAngleCheck();
	checkTurningStatus();
	if(this->state == MOVINGACROSS){
		begin_action(4.5);
	}

	publish();

}

void Possum::laser_callback(sensor_msgs::LaserScan msg)
{
	if 	((this->state == IDLE) && (this->orientation.currently_turning == false)){
		bool can_move = true;
		for (int i = 0; i<150; i++){
			if (msg.ranges[i] < 3){ //node detected
				can_move = false;
			}
		}
		if (can_move == true){
			this->state = MOVINGACROSS;
		}
	}
}

void Possum::stop(){
	if (direction == EAST){
		row = row +1;
	} else if (direction == WEST){
		row = row -1;
	}
	if (row == 8){
		direction = WEST;
		geometry_msgs::Point point;
		point.x = this->pose.px;
		point.y = this->pose.py - (this->speed.linear_x/10.0);
		for (int i = 0; i<7; i++){
			point.x = point.x - 3.5;
			action_queue.push(point);
		}	
	} else if (row == 1) {
		direction = EAST;
		geometry_msgs::Point point;
		point.x = this->pose.px;
		point.y = this->pose.py - (this->speed.linear_x/10.0);
		for (int i = 0; i<7; i++){
			point.x = point.x + 3.5;
			action_queue.push(point);
		}
	} 
	state = IDLE;
	this->speed.linear_x = 0.0;
	this->speed.angular_z = 0.0;
}
void Possum::stopTurn(){
	this->orientation.currently_turning = false;
	this->speed.linear_x = 4.0;
	this->speed.angular_z = 0.0;
}
void Possum::walk(){
	this->speed.linear_x = 1.5;
	this->speed.angular_z = 0.0;
}

void Possum::run(){
	this->speed.linear_x = 6.0;
	this->speed.angular_z = 0.0;
}
void Possum::turnLeft(){
	this->orientation.currently_turning = true;
	this->orientation.desired_angle = this->orientation.desired_angle + (M_PI / 2);
	this->speed.linear_x = 0.0;
	this->speed.angular_z = 5.0;
}
void Possum::turnRight(){
	this->orientation.currently_turning = true;
	this->orientation.desired_angle = this->orientation.desired_angle - (M_PI / 2);
	this->speed.linear_x = 0.0;
	this->speed.angular_z = -5.0;
}
//Turn back
void Possum::turnBack(){
	this->orientation.currently_turning = true;
	this->orientation.desired_angle = this->orientation.desired_angle + (M_PI);
	this->speed.linear_x = 0.0;
	this->speed.angular_z = 5.0;
}

void Possum::checkTurningStatus() //override checkTurningStatus so that linear_x = 0 after turn.
{
	if(this->orientation.currently_turning == true)
	{	
		if(doubleComparator(this->orientation.angle, this->orientation.desired_angle))
		{
			state = IDLE;
			this->orientation.currently_turning = false;
			this->speed.linear_x = 0.0;
			this->speed.angular_z = 0.0; 
		}
	return;
	}
}

char* Possum::enum_to_string(State t){
    switch(t){
        case IDLE:
            return "IDLE";
        case ROAMING:
            return "ROAMING";
        case FLEEING:
            return "FLEEING";  
        case MOVINGACROSS:
            return "MOVINGACROSS";   
        default:
            return "INVALID ENUM";
    }
 }

Possum::State Possum::generateStatus(){
	int randNum;
	srand (time(NULL));
/* generate secret number between 1 and 5: */
	randNum = rand() % 5 + 1;
	if (randNum == 1){
		return IDLE;
	}else if (randNum == 2){
		return ROAMING;
	}else if (randNum == 3){
		return FLEEING;
	}else if (randNum == 4){
		//check if possum is near vines before passing on MOVINGACROSS
		if ((this->pose.px >= -3) && (this->pose.px <= 6)){
			return MOVINGACROSS;
		} else if ((this->pose.py >= -37.5) && (this->pose.py <= 38)){
			return MOVINGACROSS;
		} else {
			return FLEEING;
		}
	} else {
		//check if possum is near vines before passing on MOVINGACROSS
		if ((this->pose.px >= -3) && (this->pose.px <= 6)){
			return MOVINGACROSS;
		} else if ((this->pose.py >= -37.5) && (this->pose.py <= 38)){
			return MOVINGACROSS;
		} else {
			return FLEEING;
		}
	}
}

void Possum::move(){}
void Possum::collisionDetected(){} 

int main(int argc, char **argv)
{	
	
//You must call ros::init() first of all. ros::init() function needs to see argc and argv. The third argument is the name of the node
ros::init(argc, argv, "POSSUM");

//NodeHandle is the main access point to communicate with ros.
ros::NodeHandle n;

//Creating the CarrierBot instance
Possum node(n);

//Setting the loop rate
ros::Rate loop_rate(10);

//a count of how many messages we have sent
int count = 0;

while (ros::ok())
{
	//node.publish();
	
	ros::spinOnce();

	loop_rate.sleep();
	++count;
}
return 0;

}