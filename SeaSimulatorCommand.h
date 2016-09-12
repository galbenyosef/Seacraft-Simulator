#ifndef SEASIMULATOR_COMMANDS_H
#define SEASIMULATOR_COMMANDS_H

#include <string>
#include <cctype>
#include <sstream>

constexpr unsigned MAX_ARGUMENTS = 7;

class SeaSimulatorCommand {

	const std::string line;

	std::string parsed_line[MAX_ARGUMENTS] = { "None","None","None","None","None","None","None" };
	unsigned argc;
	std::string name;

	bool isNumber(const std::string& );

	bool isViewCommand();
	bool isControllerCommand();
	bool isShipCommand();

public:

	SeaSimulatorCommand(const std::string& );
	SeaSimulatorCommand(const SeaSimulatorCommand&) = default;
	SeaSimulatorCommand& operator=(const SeaSimulatorCommand&);
	~SeaSimulatorCommand();

	bool operator==(const SeaSimulatorCommand& );

	bool isValid();
	const std::string& getName();
	const std::string& getArgument(unsigned);

};

#endif