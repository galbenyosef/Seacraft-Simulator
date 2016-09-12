#include "SeaObject.h"

SeaObject::SeaObject(const std::string& new_name, double x_pos, double y_pos) :name(new_name), x(x_pos), y(y_pos) {}

const std::string& SeaObject::getName() const { return name; }

 std::ostream& operator << (std::ostream& os, const SeaObject& b) {
	const std::string n = b.getName();
	std::cout << std::setprecision(2) << std::fixed << n << " " << "at: (" << b.x << ", " << b.y << "), ";
	return b.print(os); // polymorphic print via reference
}

double SeaObject::getX() const { return x; }

double SeaObject::getY() const { return y; }

void SeaObject::setX(double new_x) { x = new_x; }

void SeaObject::setY(double new_y) { y = new_y; }

SeaObject::~SeaObject() {}
