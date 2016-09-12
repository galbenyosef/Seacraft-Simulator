
#ifndef SEASIMULATOR_CONTROLLER_H
#define SEASIMULATOR_CONTROLLER_H

#include "SeaSimulatorModel.h"
#include "SeaSimulatorView.h"
#include "SeaSimulatorCommand.h"

#include "SeaObjectMaker.h"

#include <fstream>
#include <string>
#include <sstream>
#include <queue>


class SeaSimulatorController { //Singleton

	SeaSimulatorController(SeaSimulatorModel&, std::shared_ptr<SeaSimulatorView>);

	static SeaSimulatorController* inst;

	SeaSimulatorModel& model;
	std::shared_ptr<SeaSimulatorView> view;

	std::queue<SeaSimulatorCommand> commands_on_hold;

	friend class Controller_Destroyer;

public:

	static SeaSimulatorController& getInstance();

	SeaSimulatorController(const SeaSimulatorController&) = delete;
	SeaSimulatorController& operator= (const SeaSimulatorController&) = delete;
	SeaSimulatorController(SeaSimulatorController&&) = delete;
	SeaSimulatorController& operator= (const SeaSimulatorController&&) = delete;

	void start(char[]);
	//as argv[1] - port initializing file
	void readFile(char filename[]);

	void getCommandsPhrase();
	void getCommandsPhraseFile(char filename[]);

	void readCommandsPhrase();
};

#endif