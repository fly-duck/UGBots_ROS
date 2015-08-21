#include "ros/ros.h"
#include <stdlib.h>
#include <ugbots_ros/Position.h>
#include <node_structs/row.h>

class Core
{
public:
	Core(ros::NodeHandle &n)
	{
		world_layout = n.subscribe<ugbots_ros::Position>("/world_layout",1000, &Core::wl_callback, this);
	}

	void wl_callback(ugbots_ros::Position p) 
	{
		Point point;
		point.x = p.x;
		point.y = p.y;
		addBeacon(point);

		ROS_INFO("Number of Rows: %d ", rowPositions.size());
	}

	void addBeacon(Point p)
	{
		//boolean to check if the list has the point
		bool exists = false;

		//iterate through all the points in the list and check if the point exists within it
		for (std::vector<Point>::iterator point = beaconPositions.begin(); point != beaconPositions.end(); ++point) {
			Point current = *point;
			if (current.x == p.x && current.y == p.y) {
				exists = true;
				break;
			}
		}

		//if it doesn't exist append to the end of the list
		if (!exists)
		{
			beaconPositions.push_back(p);
			addPointToRow(p);
		}
	}

	void addPointToRow(Point p)
	{
		//boolean to check if the x coordinate for the row exists
		bool x_exists = false;
		//loops counter to access list element
		int i = 0;
		//initialise new row for the list of rows
		Row new_row;
		new_row.status = UNASSIGNED;

		//iterate through existing list of rows
		for (std::vector<Row>::iterator row = rowPositions.begin(); row != rowPositions.end(); ++row) {
			Row current = *row;
			//when corresponding x coordinate found
			if (current.x_pos == p.x) {
				x_exists = true;
				//if the existing start points y coordinate is greater than the new points
				//replaces the row with appropriate start/end point
				if (current.start_point.y > p.y) {
					new_row.start_point = p;
					new_row.end_point = current.start_point;
					new_row.x_pos = p.x;
					rowPositions[i] = new_row;
				//if not, new point is the end point
				} else {
					new_row.start_point = current.start_point;
					new_row.end_point = p;
					new_row.x_pos = p.x;
					rowPositions[i] = new_row;
				}
				break;
			}
			i++;
		}

		//if the x coordinate does not exist, add to row as start point
		if (!x_exists) {
			new_row.start_point = p;
			new_row.x_pos = p.x;
			rowPositions.push_back(new_row);
		}
 	}

	std::vector<Point> getBeaconList()
	{
		return beaconPositions;
	}

	ros::Subscriber world_layout;

private:
	std::vector<Point> beaconPositions;
	std::vector<Row> rowPositions;
};

int main(int argc, char **argv)
{
	// initialise node
	ros::init(argc, argv, "CORE");
	ros::NodeHandle n;

	Core c(n);

	ros::Rate loop_rate(10);

	int count = 0;
	while (ros::ok())
	{

		ros::spinOnce();
		loop_rate.sleep();
		++count;
	}

	return 0;
}
