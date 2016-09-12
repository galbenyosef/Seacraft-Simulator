#include "SeaSimulatorController.h"

class Model_Destroyer {
public:
	~Model_Destroyer() { delete SeaSimulatorModel::inst; }
} model_instance_remover;

class Controller_Destroyer {
public:
	~Controller_Destroyer() { delete SeaSimulatorController::inst; }
} controller_instance_remover;


int main(int argc, char* argv[]) {

	if (argc != 2) {
		std::cout << "Bad arguments number;";
		return 1;
	}

	char* init_file = argv[1];

	SeaSimulatorController::getInstance().start(init_file);

	//Multi commands insertion from file
	//SeaSimulatorController::getInstance().readFile(init_file);
	//SeaSimulatorController::getInstance().getCommandsPhraseFile("command_example.txt");

	return 0;
}