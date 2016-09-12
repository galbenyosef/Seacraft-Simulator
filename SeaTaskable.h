#ifndef SEATASKABLE_H
#define SEATASKABLE_H

#include "SeaSimulatorCommand.h"

#include <vector>
#include <cmath>

//an abstract class uses to store 'tasks' (execute when arrived) for each SeaCraft object
//used for 'load_at','dock_at','unload_at'

class SeaTaskable {

	std::vector<SeaSimulatorCommand> tasks;
	
public:

	SeaTaskable();
	SeaTaskable(const SeaTaskable&) = delete;
	SeaTaskable(SeaTaskable&&) = delete;
	virtual ~SeaTaskable() = 0;

	void task(const SeaSimulatorCommand& );
	void untask(SeaSimulatorCommand& );
	
	std::vector<SeaSimulatorCommand>& getTasks();

	bool taskExist();
};

#endif