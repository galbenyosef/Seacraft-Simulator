#ifndef SEASIMULATOR_MODEL_H
#define SEASIMULATOR_MODEL_H

#include "SeaExceptions.h"

#include "SeaCraft.h"
#include "SeaPort.h"
#include "CargoShip.h"
#include "PirateShip.h"

static constexpr auto PirateShipNameConvention = "Cruiser";
static constexpr auto CargoShipNameConvention = "Freighter";

class SeaSimulatorModel { //Singleton

	SeaSimulatorModel();

	static SeaSimulatorModel* inst;
	std::vector< std::shared_ptr<SeaCraft> > ships;
	std::vector< std::shared_ptr<SeaPort> > ports;

	friend class Model_Destroyer;

	unsigned timer;

public:

	static SeaSimulatorModel& getInstance();

	SeaSimulatorModel(const SeaSimulatorModel&) = delete;
	SeaSimulatorModel& operator= (const SeaSimulatorModel&) = delete;
	SeaSimulatorModel(const SeaSimulatorModel&&) = delete;
	SeaSimulatorModel& operator= (SeaSimulatorModel&&) = delete;

	void add(std::shared_ptr<SeaCraft> );
	void add(std::shared_ptr<SeaPort> );

	void resetTimer();
	unsigned getTimer() const;

	const std::string whoIsAt(double , double , double , double ) const;

	std::shared_ptr<SeaCraft> getSeaCraftByName(const std::string& toFind) const;
	std::shared_ptr<SeaPort> getSeaPortByName(const std::string& toFind) const;
	std::shared_ptr<SeaPort> getSeaPortByXY(double x, double y) const;
	std::shared_ptr<SeaObject> getSeaObjectByName(const std::string& toFind) const;

	void update();

	void status();
};

#endif