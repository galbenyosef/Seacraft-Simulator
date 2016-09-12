#include "SeaMoveable.h"

double distanceCalculate(double x1, double y1, double x2, double y2)
{
	double x = x1 - x2;
	double y = y1 - y2;
	double dist;

	dist = pow(x, 2) + pow(y, 2);           //calculating distance by euclidean formula
	dist = sqrt(dist);                  //sqrt is function in math.h

	return dist;
}

SeaMoveable::SeaMoveable(double hisX, double hisY) { cartesian.cur_x = hisX; cartesian.cur_y = hisY; speed = 0; polar.thetha = 0; }

void SeaMoveable::stop() { speed = 0; }

void SeaMoveable::navigateTo(double fromX, double fromY, double toX, double toY, double _speed) {

	cartesian.inUse = true;
	polar.inUse = false;

	cartesian.cur_x = fromX;
	cartesian.cur_y = fromY;
	cartesian.dst_x = toX;
	cartesian.dst_y = toY;

	speed = _speed;

} //moving to

void SeaMoveable::moveTo(double _thetha, double _speed) {

	cartesian.inUse = false;
	polar.inUse = true;
	polar.thetha = _thetha;

	//SeaAngle to standard 2D axis angle convertion
	if (_thetha >= 0 && _thetha <= 90)
		polar.thetha = 90 - _thetha;
	else {
		polar.thetha = 360 + 90 - _thetha;
	}
	polar.thetha = polar.thetha*PI / 180;
	speed = _speed;

}// moving on course

void SeaMoveable::setSpeed(double new_sp) { speed = new_sp; }

double SeaMoveable::getSpeed() const { return speed; }

double SeaMoveable::getAngle() const {
	return polar.thetha;
}

void SeaMoveable::move() {

	double new_x_diff;
	double new_y_diff;

	if (cartesian.inUse) {
		//cartesian params
		double r = distanceCalculate(cartesian.cur_x, cartesian.cur_y, cartesian.dst_x, cartesian.dst_y);
		//target reached check
		if (speed >= r) {
			cartesian.cur_x = cartesian.dst_x;
			cartesian.cur_y = cartesian.dst_y;
			return;
		}

		polar.thetha = atan2((cartesian.dst_y - cartesian.cur_y), (cartesian.dst_x - cartesian.cur_x));

		if (polar.thetha < 0.) {
			polar.thetha = 2. * PI + polar.thetha;
		}
		//new difference for x,y
		new_x_diff = speed*std::cos(polar.thetha);
		new_y_diff = speed*std::sin(polar.thetha);
		//update current x,y
		cartesian.cur_x += new_x_diff;
		cartesian.cur_y += new_y_diff;
	}
	else {
		//polar params
		new_x_diff = speed*std::cos(polar.thetha);
		new_y_diff = speed*std::sin(polar.thetha);

		cartesian.cur_x += new_x_diff;
		cartesian.cur_y += new_y_diff;
	}
}

double SeaMoveable::getCurrentX() { return cartesian.cur_x; }

double SeaMoveable::getCurrentY() { return cartesian.cur_y; }

double SeaMoveable::getDestinationX() { return cartesian.dst_x; }

double SeaMoveable::getDestinationY() { return cartesian.dst_y; }

bool SeaMoveable::hasReachedDestination() {
	if (cartesian.cur_x == cartesian.dst_x && cartesian.cur_y == cartesian.dst_y)
		return true;
	return false;
}

SeaMoveable::~SeaMoveable() {}
