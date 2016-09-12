#ifndef SEAOBJECT_H
#define SEAOBJECT_H

#include <string>
#include <memory>
#include <iostream>
#include <list>
#include <iomanip>

class SeaObject {

protected:

	virtual std::ostream& print(std::ostream& a) const = 0;

	const std::string name;
	double x, y;

public:

	SeaObject(const std::string& new_name, double x_pos, double y_pos);
	SeaObject(const SeaObject&) = delete;
	SeaObject& operator= (const SeaObject&) = delete;
	SeaObject(SeaObject&&) = delete;
	SeaObject& operator= (SeaObject&&) = delete;
	virtual ~SeaObject() = 0;

	const std::string& getName() const;

	friend std::ostream& operator << (std::ostream& os, const SeaObject& b);

	double getX() const;
	double getY() const;
	void setX(double new_x);
	void setY(double new_y);
};

#endif