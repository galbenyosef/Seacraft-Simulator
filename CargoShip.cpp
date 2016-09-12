#include "CargoShip.h"

CargoShip::CargoShip(const std::string& new_name, double x_pos, double y_pos, unsigned cargo_capacity, unsigned resistance)
	: SeaCraft(new_name, x_pos, y_pos), init_containers(cargo_capacity) {

	craft_args[RESISTANCE] = resistance;
	craft_args[CONTAINERS] = cargo_capacity;
	craft_args[FUEL] = SPAWN_DEFAULT_FUEL;

}

std::ostream& CargoShip::printCraft(std::ostream& os) const {

	return os << "Containers: " << craft_args[0] <<
		", Resistance: " << craft_args[1] <<
		", Fuel: " << craft_args[2] << ", ";
}

CargoShip::~CargoShip()
{
}

void CargoShip::dock() { setStatus("Docked"); }

void CargoShip::load() { craft_args[CONTAINERS] = init_containers; }

void CargoShip::unload(unsigned dec) { 
	if (craft_args[CONTAINERS] <= dec) { 
		craft_args[CONTAINERS] = 0; 
	} 
	else { 
		craft_args[CONTAINERS] -= dec;
	}
}

unsigned CargoShip::refuel(unsigned inc) {
	if (craft_args[FUEL] + inc <= SPAWN_DEFAULT_FUEL) {
		craft_args[FUEL] += inc;
		return inc;
	}
	else {
		unsigned used;
		used = SPAWN_DEFAULT_FUEL - craft_args[FUEL];
		craft_args[FUEL] = SPAWN_DEFAULT_FUEL;
		return used;
	}
}

unsigned CargoShip::getResistance() const { return craft_args[RESISTANCE]; }

unsigned CargoShip::getFuel() const { return craft_args[FUEL]; }

unsigned CargoShip::getContainers() const { return craft_args[CONTAINERS]; }

void CargoShip::setLoser() { craft_args[CONTAINERS] = 0; }

void CargoShip::decFuel(unsigned dec) {
	if (dec > craft_args[FUEL]) {
		craft_args[FUEL] = 0;
	}
	else {
		craft_args[FUEL] -= dec;
	}
}
