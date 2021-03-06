// Bring in gtest
#include <gtest/gtest.h>

#include "ros/ros.h"
#include "std_msgs/String.h"
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/LaserScan.h>

#include <sstream>
#include <stdlib.h>

#include <node_defs/visitor.h>

// the node
static Visitor node;

void setup()
{
	// create a new instance of visitor
	node = Visitor();
}

//######################### UNIT TESTS #########################

TEST(UnitTest, testNodeInitialisedSpeed)
{
	setup();

	EXPECT_EQ(node.speed.linear_x, 0.0);
	EXPECT_EQ(node.speed.angular_z, 0.0);
}

TEST(UnitTest, testNodeTopSpeed)
{
	setup();

	EXPECT_EQ(node.speed.max_linear_x, 3.0);
}

TEST(UnitTest, testStartupState)
{
	setup();

	EXPECT_EQ(node.state, Visitor::IDLE); 
}

TEST(UnitTest, testWaiting)
{
	node.waiting();
	EXPECT_EQ(node.speed.linear_x, 0.0);
}

//###################### ACCEPTANCE TESTS ######################

//Initialises a route and tests that it is added to the action_queue
TEST(AcceptanceTest, testActionQueueInit)
{
	setup();

	node.init_route();
	EXPECT_TRUE(!node.action_queue.empty());
}

TEST(AcceptanceTest, testTurnStop)
{
	setup();

	node.orientation.currently_turning = true;
	node.orientation.desired_angle = node.orientation.angle;

	node.checkTurningStatus();

	EXPECT_FALSE(node.orientation.currently_turning);
}

TEST(AcceptanceTest, testStartTour)
{
	node.startTour();
	EXPECT_EQ(node.speed.linear_x, 2.0);
}

// Run all the tests that were declared with TEST()
int main(int argc, char **argv){
	//Create a node to test with
	ros::init(argc, argv, "VISITOR");
	ros::NodeHandle n;

	//Run the test suite
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}