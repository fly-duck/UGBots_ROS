// Bring in gtest
#include <gtest/gtest.h>

#include "ros/ros.h"
#include "std_msgs/String.h"
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/LaserScan.h>

#include <sstream>
#include <stdlib.h>

#include <node_defs/dog.h>

static Dog node;

void setup()
{
	// create a new instance of node
	node = Dog();
}

//######################### UNIT TESTS #########################

TEST(UnitTest, testNodeInitialisedSpeed)
{
	EXPECT_EQ(node.speed.linear_x, 0.0);
	EXPECT_EQ(node.speed.angular_z, 0.0);
}

TEST(UnitTest, testNodeTopSpeed)
{
	EXPECT_EQ(node.speed.max_linear_x, 6.0);
}

TEST(UnitTest, testStartupState)
{
	EXPECT_EQ(node.state, Dog::IDLE); 
}

//###################### ACCEPTANCE TESTS ######################

TEST(AcceptanceTest, testTurnStop)
{
	setup();

	node.orientation.currently_turning = true;
	node.orientation.desired_angle = node.orientation.angle;

	node.checkTurningStatus();

	EXPECT_FALSE(node.orientation.currently_turning);
}

TEST(AcceptanceTest, testChangeStatus)
{
	node.turnRandomly();

	EXPECT_TRUE(node.orientation.currently_turning);
}

// Run all the tests that were declared with TEST()
int main(int argc, char **argv){
	//Create a node to test with
	ros::init(argc, argv, "DOG");
	ros::NodeHandle n;

	//Run the test suite
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}