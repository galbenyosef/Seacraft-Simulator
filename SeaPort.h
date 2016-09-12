#ifndef SEAPORT_H
#define SEAPORT_H

#include "SeaObject.h"

class SeaPort : public SeaObject {

	std::ostream& print(std::ostream&) const;

	unsigned fuel_capacity;
	const unsigned fuel_production;

public:

	SeaPort(const std::string&,double,double,unsigned,unsigned);
	SeaPort(const SeaPort&) = delete;
	SeaPort& operator=(const SeaPort&) = delete;
	SeaPort(SeaPort&&) = delete;
	SeaPort& operator=(SeaPort&&) = delete;
	~SeaPort() {}

	unsigned getFuelCapacity()const;
	void produce();
	void decFuel(unsigned);

};

#endif