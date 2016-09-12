#include "PirateShip.h"

std::ostream& PirateShip::printCraft(std::ostream& os) const {

	return os << "Force: " << craft_args[FORCE] << ", ";
}

PirateShip::PirateShip(const std::string& new_name, double x_pos, double y_pos, unsigned force, unsigned range)
	: SeaCraft(new_name, x_pos, y_pos) {

	craft_args[FORCE] = force;
	craft_args[RANGE] = range;

}

bool PirateShip::attack(unsigned cargo_resistance) {
	if (craft_args[FORCE] > cargo_resistance) { ++craft_args[FORCE]; return true; }
	else { return false; }
}

unsigned PirateShip::getRange() const { return craft_args[RANGE]; }

void PirateShip::setLoser() { if (craft_args[FORCE] < 2) { craft_args[FORCE] = 0; } else { --craft_args[FORCE]; } }

PirateShip::~PirateShip() {}
