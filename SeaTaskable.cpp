#include "SeaTaskable.h"

SeaTaskable::SeaTaskable() {}

void SeaTaskable::task(const SeaSimulatorCommand& new_task) { tasks.push_back(new_task); }

void SeaTaskable::untask(SeaSimulatorCommand& task) {

	std::vector<SeaSimulatorCommand>::iterator it;

	for (it = tasks.begin(); it != tasks.end(); it++) {
		if (*it == task) {
			tasks.erase(it);
		}
	}
}

std::vector<SeaSimulatorCommand>& SeaTaskable::getTasks() { return tasks; }

bool SeaTaskable::taskExist() { return tasks.size() > 0 ? 1 : 0; }

SeaTaskable::~SeaTaskable() {}
