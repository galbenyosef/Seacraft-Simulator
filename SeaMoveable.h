#ifndef SEAMOVEABLE_H
#define SEAMOVEABLE_H

#include <cmath>

const auto PI = 2. * atan2(1., 0.);
double distanceCalculate(double x1, double y1, double x2, double y2);

//abstract class SeaMoveable, giving derived object the move() function, including other usefull axis movement functions
class SeaMoveable {

	double speed;

	//cartesian movement params
	struct _cartesian {

		bool inUse;
		double cur_x, cur_y, dst_x, dst_y;

	} cartesian;
	//polar movement params
	struct _polar {

		bool inUse;
		double thetha;

	} polar;

public:

	SeaMoveable(double, double);
	SeaMoveable(const SeaMoveable&) = delete;
	SeaMoveable& operator= (const SeaMoveable&) = delete;
	SeaMoveable(SeaMoveable&&) = delete;
	SeaMoveable& operator= (const SeaMoveable&&) = delete;
	virtual ~SeaMoveable() = 0;

	//speed value as 0 makes no move
	void stop();
	//movement functions, navigateTo specific coordinate, move to specific direction
	void navigateTo(double , double , double , double , double );
	void moveTo(double , double );

	void setSpeed(double );
	double getSpeed() const;
	double getAngle() const;

	//indicates by 'in use' which movement is used and then calculates next coordinate
	void move();

	double getCurrentX();
	double getCurrentY();
	double getDestinationX();
	double getDestinationY();

	bool hasReachedDestination();
};

#endif