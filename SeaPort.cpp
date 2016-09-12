#include "SeaPort.h"

std::ostream& SeaPort::print(std::ostream& os) const {
	return os << "Fuel: " << fuel_capacity << ", Production: " << fuel_production;
}

SeaPort::SeaPort(const std::string& new_name, double x_pos, double y_pos, unsigned fuel_cap, unsigned fuel_prod)
	: SeaObject(new_name, x_pos, y_pos), fuel_capacity(fuel_cap), fuel_production(fuel_prod) {}

unsigned SeaPort::getFuelCapacity()const {
	return fuel_capacity;
}

void SeaPort::produce() {
	fuel_capacity += fuel_production;
}

void SeaPort::decFuel(unsigned dec) {
	if (dec > fuel_capacity) {
		fuel_capacity = 0;
	}
	else {
		fuel_capacity -= dec;
	}
}
