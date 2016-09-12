#ifndef PIRATE_SHIP_H
#define PIRATE_SHIP_H

#include "SeaCraft.h"

//arg0 - force
constexpr unsigned FORCE = 0;
//arg1 - attack range
constexpr unsigned RANGE = 1;

class PirateShip :  public SeaCraft {

	//print object method
	std::ostream& printCraft(std::ostream& os) const;

public:

	PirateShip(const std::string& , double , double , unsigned , unsigned );
	PirateShip(const PirateShip&) = delete;
	PirateShip& operator= (const PirateShip&) = delete;
	PirateShip(PirateShip&&) = delete;
	PirateShip& operator= (const PirateShip&&) = delete;

	virtual ~PirateShip();

	bool attack(unsigned);
	unsigned getRange() const;
	void setLoser();

};

#endif