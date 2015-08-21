#include <node_structs/point.h>
#include <string>

struct Row {
	enum Status {UNASSIGNED, ASSIGNED}

	Point end_point;
	Point start_point;
	double x_pos;
	Status status;
};
