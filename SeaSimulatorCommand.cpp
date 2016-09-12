#include "SeaSimulatorCommand.h"

bool SeaSimulatorCommand::isNumber(const std::string& str) {

	double num;
	std::istringstream iss(str);
	try {
		iss >> num;
		return true;
	}
	catch (...) {
		return false;
	}


}

bool SeaSimulatorCommand::isViewCommand() {

	std::string& command_name = parsed_line[0];

	if (command_name == "default" && argc == 1) {
		return true;
	}

	if (command_name == "show" && argc == 1) {
		return true;
	}
	if (command_name == "size" && argc == 2) {
		if (isNumber(parsed_line[1])) {
			if (stoi(parsed_line[1]) > 5 && stoi(parsed_line[1]) < 31) {
				return true;
			}
		}
	}
	if (command_name == "zoom" && argc == 2) {
		if (isNumber(parsed_line[1])) {
			if (stoi(parsed_line[1]) > 0) {
				return true;
			}
		}
	}
	if (command_name == "pan" && argc == 3) {
		if (isNumber(parsed_line[1]) && isNumber(parsed_line[2])) {
			return true;
		}
	}
	if (command_name == "view" && argc == 1) {
		return true;
	}

	return false;
}

bool SeaSimulatorCommand::isControllerCommand() {

	std::string& command_name = parsed_line[0];
	if (command_name == "quit" && argc == 1) {
		return true;
	}
	if (command_name == "go" && argc == 1) {
		return true;
	}
	if (command_name == "status" && argc == 1) {
		return true;
	}
	if (command_name == "create" && argc == 7) {
		if (0 < getArgument(1).length() && getArgument(1).length() < 13) {
			if (isNumber(getArgument(3)) && isNumber(getArgument(4))
				&& isNumber(getArgument(5)) && isNumber(getArgument(6))) {
				return true;
			}
		}
	}
	return false;
}

bool SeaSimulatorCommand::isShipCommand() {

	if (argc < 2) {
		return false;
	}
	std::string& command_name = parsed_line[1];
	command_name = parsed_line[1];
	if (command_name == "course" && argc == 4) {
		return true;
	}
	else if (command_name == "position" && argc == 5) {
		return true;
	}
	else if (command_name == "destination" && argc == 4) {
		return true;
	}
	else if (command_name == "load_at" && argc == 3) {
		return true;
	}
	else if (command_name == "unload_at" && argc == 4) {
		return true;
	}
	else if (command_name == "dock_at" && argc == 3) {
		return true;
	}
	else if (command_name == "attack" && argc == 3) {
		return true;
	}
	else if (command_name == "refuel" && argc == 2) {
		return true;
	}
	else if (command_name == "stop" && argc == 2) {
		return true;
	}
	return false;
}

SeaSimulatorCommand::SeaSimulatorCommand(const std::string& args) :line(args), name(parsed_line[0]) {
	argc = 0;
	std::string fixedline;

	for (size_t i = 0; i < line.size(); ++i) {
		if (line[i] != '(' && line[i] != ')' && line[i] != ',') fixedline += line[i];
	}
	std::istringstream iss(fixedline);
	for (size_t i = 0; i < MAX_ARGUMENTS && !iss.eof(); i++) {
		iss >> parsed_line[i];
		++argc;
	}

}

SeaSimulatorCommand& SeaSimulatorCommand::operator=(const SeaSimulatorCommand& other){
  
  if (this != &other){
    this->argc = other.argc;
    this->name = other.name;
    for (size_t i = 0;i<MAX_ARGUMENTS;i++){
      this->parsed_line[i] = other.parsed_line[i];
    }
  }
  return *this;
}

SeaSimulatorCommand::~SeaSimulatorCommand(){
}

bool SeaSimulatorCommand::operator==(const SeaSimulatorCommand& rhs) {
	for (unsigned j = 0; j < MAX_ARGUMENTS; j++) {
		if (parsed_line[j] != rhs.parsed_line[j]) {
			return false;
		}
	}
	return true;
}

bool SeaSimulatorCommand::isValid() {

	if (isViewCommand() || isControllerCommand()) {
		name = parsed_line[0];
		return true;
	}
	else if (isShipCommand()) {
		name = parsed_line[1];
		return true;
	}
	return false;
}

const std::string& SeaSimulatorCommand::getName() {

	return name;

}

const std::string& SeaSimulatorCommand::getArgument(unsigned i) { return parsed_line[i]; }
