#ifndef CARGO_SHIP_H
#define CARGO_SHIP_H

#include "SeaCraft.h"

//default fuel tank size
constexpr unsigned SPAWN_DEFAULT_FUEL = 500;
//arg0 - capacity of cargo
constexpr unsigned CONTAINERS = 0;
//arg1 - resistance points
constexpr unsigned RESISTANCE = 1;
//arg2 - capacity of fuel
constexpr unsigned FUEL = 2;

class CargoShip : public SeaCraft {

	//print object method
	std::ostream& printCraft(std::ostream&) const;
	
	const unsigned init_containers;

public:

	CargoShip(const std::string&, double, double, unsigned, unsigned);
	CargoShip(const CargoShip&) = delete;
	CargoShip& operator= (const CargoShip&) = delete;
	CargoShip(CargoShip&&) = delete;
	CargoShip& operator= (CargoShip&&) = delete;
	virtual ~CargoShip();

	void dock();
	void load();
	void unload(unsigned dec);
	unsigned refuel(unsigned inc);

	unsigned getResistance() const;
	unsigned getFuel() const;
	unsigned getContainers() const;

	void setLoser();
	void decFuel(unsigned dec);

};

#endif