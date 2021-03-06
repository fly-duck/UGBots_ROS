/*
 * Author: UGBots
 * 
 * Members: Andy Choi, Kevin Choi, Andrew Jeoung, Jay Kim, Jenny Lee, Namjun Park, Harvey Rendell, Chuan-Yu Wu
 * 
 * This class is for basic visitor movements
 */

#include "ros/ros.h"
#include "std_msgs/String.h"
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/LaserScan.h>

#include <sstream>
#include <stdlib.h>
#include <node_defs/visitor.h>
#include <iterator>

Visitor::Visitor()
{
	//setting base attribute defaults
	pose.theta = M_PI/2.0;
	pose.px = 10;
	pose.py = 20;
	speed.linear_x = 0.0;
	speed.max_linear_x = 3.0;
	speed.angular_z = 0.0;
	state = IDLE;
}

Visitor::Visitor(ros::NodeHandle &n)
{
	//setting base attribute defaults
	this->pose.theta = M_PI/2.0;
	this->pose.px = -40;
	this->pose.py = -44;
	this->speed.linear_x = 0.0;
	this->speed.max_linear_x = 3.0;
	this->speed.angular_z = 0.0;
	this->state = IDLE;

	this->orientation.previous_right_distance = 0;
	this->orientation.previous_left_distance = 0;
	this->orientation.previous_front_distance = 0;
	this->orientation.angle = 0;
	this->orientation.desired_angle = 0;

	this->orientation.currently_turning = false;
	this->orientation.currently_turning_static = false;

	this->rightTurnInit = false;
	this->leftTurnInit = false;
	this->queueDuplicateCheckAngle = 0.0;
	this->queueDuplicate = true;
	this->tourStarted = false;

	this->sub_list.node_stage_pub = n.advertise<geometry_msgs::Twist>("cmd_vel",1000);
	this->sub_list.sub_odom = n.subscribe<nav_msgs::Odometry>("base_pose_ground_truth",1000, &Visitor::odom_callback, this);
	this->sub_list.sub_laser = n.subscribe<sensor_msgs::LaserScan>("base_scan",1000,&Visitor::laser_callback, this);
	//for core callbacks
	this->sub_row = n.subscribe<ugbots_ros::Position>("/row_loc",1000,&Visitor::core_callback, this);

	this->waitingInLine = true;
	this->state = IDLE;
	//init_route();

}

void Visitor::odom_callback(nav_msgs::Odometry msg)
{
	//This is the call back function to process odometry messages coming from Stage. 	
	this->pose.px = msg.pose.pose.position.x;
	this->pose.py = msg.pose.pose.position.y;
	this->orientation.rotx = msg.pose.pose.orientation.x;
	this->orientation.roty = msg.pose.pose.orientation.y;
	this->orientation.rotz = msg.pose.pose.orientation.z;
	this->orientation.rotw = msg.pose.pose.orientation.w;

	calculateOrientation();

	if(!waitingInLine)//if not waiting in line start actions
	{
		begin_action_shortest_path(2.0);
	}

	doAngleCheck();		//angle orientation check

	checkTurningStatus();  // turning check

	publish();

	ROS_INFO("/position/x/%f",this->pose.px);
	ROS_INFO("/position/y/%f",this->pose.py);
	ROS_INFO("/status/%s/./", enum_to_string(state));
}


void Visitor::laser_callback(sensor_msgs::LaserScan msg)
{

	if(insideFarm()) // if inside farm
	{	
		if(fabs(this->queueDuplicateCheckAngle - this->orientation.angle) >= (M_PI/2.000000))//after initial turn, turn avoiding on again
		{
			this->queueDuplicate = true;
			this->queueDuplicateCheckAngle = 0;
		}
		
		//if something is in front, initiate avoidance mechanism
		for(int i=88; i<93; i++)
		{
			if(msg.ranges[i] < 2.0)// if less than 2.0
			{
				if(this->queueDuplicate == true) //and if avoidance has not just started
				{
					this->queueDuplicateCheckAngle = this->orientation.angle;

					std::queue<geometry_msgs::Point> temp_queue;

					geometry_msgs::Point pointtemp;

					//45 degrees clockwise
					pointtemp.x = this->pose.px + sqrt(8) * cos(this->orientation.angle - (M_PI/4.0));
					pointtemp.y = this->pose.py + sqrt(8) * sin(this->orientation.angle - (M_PI/4.0));
					temp_queue.push(pointtemp);
					//45 degrees anticlockwise
					pointtemp.x = pointtemp.x + sqrt(8) * cos(this->orientation.angle + (M_PI/4.0));
					pointtemp.y = pointtemp.y + sqrt(8) * sin(this->orientation.angle + (M_PI/4.0));
					temp_queue.push(pointtemp);

					while(!action_queue.empty())//empty the action queue into temp
					{
						temp_queue.push(action_queue.front());
						action_queue.pop();
					}

					while(!temp_queue.empty())//reinitialise action queue
					{
						action_queue.push(temp_queue.front());
						temp_queue.pop();
					}

					this->queueDuplicate = false;
				}
				break;
			}
		}
	}
	else
	{
		if(!tourStarted) //if the tour has not started
		{
			if(msg.ranges[90] > 5)//if person in front has started
			{
				if(msg.ranges[0] > 15) // and worker is not around
				{
					this->speed.linear_x = 0.5;
				}
			}
			else if(msg.ranges[90] <= 5) // if person in front stops, stop
			{
				this->speed.linear_x = 0.0;
				return;
			}

			if(msg.ranges[0] > 5 && msg.ranges[0] < 15) //stop if worker is there
			{
				waiting();
			}
			
			if(msg.ranges[0] < 4.5) //start tour if worker gives the go sign
			{
				startTour();
			}
		}
		else
		{
			if(msg.ranges[90] < 2)// tour finished, form a line outside the farm
			{
				waitingInLine = true;
				stop();
			}
		}
	}
}

//method for getting the beacon co-ordinates from the core
void Visitor::core_callback(ugbots_ros::Position msg)
{
	geometry_msgs::Point pointtemp;
	pointtemp.x = msg.x; 
	pointtemp.y = msg.y;

	this->beacon_points.push_back(pointtemp);//push into a queue
}

void Visitor::checkTurningStatus()
{
		//Implement individually.
		//Change 2-3 to which ever suits your node
		//parse in ur desired linear speed to stopTurn()
		
	if(this->orientation.currently_turning == true)
	{
		if(doubleAngleComparator(this->orientation.angle , this->orientation.desired_angle))
		{
			this->orientation.currently_turning = false;
			this->speed.linear_x = 2.0;
			this->speed.angular_z = 0.0;
		}
	}
}

//for testing purposes only
void Visitor::init_route()
{
	geometry_msgs::Point point;
		point.x = 10.5; 
		point.y = -39.0;

	action_queue.push(point);
	
		point.x = 10.5;
		point.y = 39.0;

	action_queue.push(point);

		point.x = 3.5;
		point.y = 39.0;

	action_queue.push(point);

		point.x = 3.5;
		point.y = -39.0;

	action_queue.push(point);

		point.x = -3.5;
		point.y = -39.0;

	action_queue.push(point);

		point.x = -3.5;
		point.y = 39.0;

	action_queue.push(point);

		point.x = -10.5;
		point.y = 39.0;

	action_queue.push(point);

		point.x = -10.5;
		point.y = -39.0;

	action_queue.push(point);

		point.x = 52.0;
		point.y = -48.5;

	action_queue.push(point);
}

/*set up the initial route according to the number of rows from the 
* queue made from beacon callbacks.
*/
void Visitor::doRouteSetup()
{
	//decisions are easily configurable but for the final version
	//decided that the visitor will go to the first and the last row
	//before returning
	geometry_msgs::Point begin_low;
	geometry_msgs::Point begin_high;
	geometry_msgs::Point end_high;
	geometry_msgs::Point end_low;

	double lowest_x = 0.0;
	double highest_x = 0.0;

	std::list<geometry_msgs::Point>::iterator iter;
	//loop through to find the first and the last beacon
	for(iter = beacon_points.begin(); iter != beacon_points.end(); iter++)
	{
		geometry_msgs::Point temp;
		temp = *iter;
		if(temp.x < lowest_x || doubleComparator(temp.x, lowest_x))
		{
			lowest_x = temp.x;

			if(temp.y < 0)
			{
				end_low.y = temp.y;
				end_low.x = temp.x;
			}
		}
		else if (temp.x > highest_x || doubleComparator(temp.x, highest_x))
		{
			highest_x = temp.x;

			if(temp.y < 0)
			{
				begin_low.y = temp.y;
				begin_low.x = temp.x;
			}
		}
	}

	begin_high.x = begin_low.x;
	begin_high.y = begin_low.y * -1.0;

	end_high.x = end_low.x;
	end_high.y = end_low.y * -1.0;
	//add the beacons to the queue
	action_queue.push(begin_low);
	action_queue.push(begin_high);
	action_queue.push(end_high);
	action_queue.push(end_low);
	//initialise the exit queue
	geometry_msgs::Point exitRoute;
	exitRoute.x = 52.0;
	exitRoute.y = -46.0;

	action_queue.push(exitRoute);

	exitRoute.x = 52.0;
	exitRoute.y = -15.0;

	action_queue.push(exitRoute);	
}

void Visitor::waiting()//change variables for waiting 
{
	this->waitingInLine = true;
	this->speed.linear_x = 0.0;
	this->speed.angular_z = 0.0;

}

void Visitor::startTour()//change variables for starting tour
{
	this->tourStarted = true;
	this->waitingInLine = false;
	this->speed.linear_x = 2.0;
	this->state = TOURING;
	doRouteSetup();
}

bool Visitor::insideFarm()//check if the worker is inside farm
{
	if(this->pose.px > 50.0 || this->pose.px < -50.0)
	{
		return false;
	}
	
	if(this->pose.py > 50.0 || this->pose.py < -50.0)
	{
		return false;
	}

	return true;
}

void Visitor::move(){}

void Visitor::stop(){
	this->speed.linear_x = 0.0;
	this->speed.angular_z = 0.0;
}

void Visitor::turnLeft(){}
void Visitor::turnRight(){}
void Visitor::collisionDetected(){}
char const* Visitor::enum_to_string(State t)
{
	switch(t){
		case IDLE:
			return "IDLE";
		case AVOIDING:
			return "AVOIDING";
		case TOURING:
			return "TOURING";
		default:
			return "";
	}
}

int main(int argc, char **argv)
{	
	
//You must call ros::init() first of all. ros::init() function needs to see argc and argv. The third argument is the name of the node
ros::init(argc, argv, "VISITOR");

//NodeHandle is the main access point to communicate with ros.
ros::NodeHandle n;

//Creating the CarrierBot instance
Visitor node(n);

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
