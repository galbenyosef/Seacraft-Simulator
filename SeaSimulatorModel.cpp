#include "SeaSimulatorModel.h"

SeaSimulatorModel::SeaSimulatorModel() { resetTimer(); }

void SeaSimulatorModel::add(std::shared_ptr<SeaCraft> newobj) { ships.push_back(newobj); }

void SeaSimulatorModel::add(std::shared_ptr<SeaPort> newobj) { ports.push_back(newobj); }

void SeaSimulatorModel::resetTimer() { timer = 0; }

unsigned SeaSimulatorModel::getTimer() const { return timer; }

const std::string SeaSimulatorModel::whoIsAt(double start_x, double end_x, double start_y, double end_y) const {

	for (auto i : ports) {
		double hisX, hisY;
		hisX = i->getX();
		hisY = i->getY();
		if (hisX >= start_x && hisX < end_x && hisY >= start_y && hisY < end_y)
			return i->getName();
	}
	for (auto i : ships) {
		double hisX, hisY;
		hisX = i->getX();
		hisY = i->getY();
		if (hisX >= start_x && hisX < end_x && hisY >= start_y && hisY < end_y)
			return i->getName();
	}
	return "";
}

std::shared_ptr<SeaCraft> SeaSimulatorModel::getSeaCraftByName(const std::string& toFind) const{

	for (auto i : ships) {
		std::string hisName;
		hisName = i->getName();
		if (hisName == toFind)
			return (i);
	}
	throw SeaObjectNotFound(toFind);
}

std::shared_ptr<SeaPort> SeaSimulatorModel::getSeaPortByName(const std::string& toFind) const{

	for (auto i : ports) {
		std::string hisName;
		hisName = i->getName();
		if (hisName == toFind)
			return (i);
	}
	throw SeaObjectNotFound(toFind);
}

std::shared_ptr<SeaPort> SeaSimulatorModel::getSeaPortByXY(double x, double y) const{

	for (auto i : ports) {
		double hisX, hisY;
		hisX = i->getX();
		hisY = i->getY();

		if (hisX == x && hisY == y)
			return (i);
	}
	throw SeaObjectNotFound("coordinates: "  + '(' + (int)x + ',' + (int)y + ')');
}

std::shared_ptr<SeaObject> SeaSimulatorModel::getSeaObjectByName(const std::string& toFind) const{

	if (getSeaCraftByName(toFind) != nullptr)
		return getSeaCraftByName(toFind);
	if (getSeaPortByName(toFind) != nullptr)
		return getSeaPortByName(toFind);
	throw SeaObjectNotFound(toFind);

}

void SeaSimulatorModel::update() {
	std::shared_ptr<SeaPort> port;
	std::shared_ptr<CargoShip> cargo_ship;

	//for all seacraft
	for (auto i : ships) {

		bool is_cargo_ship = typeid(CargoShip) == typeid(*i) ? 1 : 0;
		//if ship is a cargo
		if (is_cargo_ship) {
			cargo_ship = std::static_pointer_cast<CargoShip>(i);
			//and has fuel
			if (cargo_ship->getFuel() > 0) {
				i->move();
				i->setX(i->getCurrentX());
				i->setY(i->getCurrentY());
				cargo_ship->decFuel((unsigned)(i->getSpeed()));
				//if tasks exists
				if (i->taskExist()) {
					//get them
					for (auto& j : i->getTasks()) {
						//if craft has reached destination and destination is valid port
						if (i->hasReachedDestination() && (port = getSeaPortByXY(i->getX(), i->getY())) != nullptr) {
							//check if founded port is the tasked one
							if (port->getName() == j.getArgument(2)) {
								//choose command
								if (j.getName() == "load_at") {
									cargo_ship->load();
									i->untask(j);
								}
								else if (j.getName() == "unload_at") {
									cargo_ship->unload(std::stoul(j.getArgument(3)));
									i->untask(j);
								}
								else if (j.getName() == "dock_at") {
									cargo_ship->dock();
									i->untask(j);
								}
							}
						}
					}
				}
			}
			//no fuel
			else {
				cargo_ship->stop();
				cargo_ship->setStatus("Stuck");
			}
		}
		//if ship is a pirate ship
		else {
			i->move();
			i->setX(i->getCurrentX());
			i->setY(i->getCurrentY());
		}
		//if any of them reached destination make them stop
		if (i->hasReachedDestination()) {
			i->stop();
			i->setStatus("Stopped");
		}
	}
	//for all seaports
	for (auto i : ports) {
		i->produce();
	}

	++timer;
}

void SeaSimulatorModel::status() {

	for (auto i : ports) {
		std::cout << "Port " << *i << std::endl;
	}
	for (auto i : ships) {
		//ship is a cargo ship
		if (typeid(*i) == typeid(CargoShip)) {
			std::string retval;
			std::string destination;
			//destination and tasks print
			if (i->getStatus() == "MovingTo") {
				//if destination is a port
				if (getSeaPortByXY(i->getDestinationX(), i->getDestinationY()) != nullptr) {
					//his name
					destination = getSeaPortByXY(i->getDestinationX(), i->getDestinationY())->getName();
					std::ostringstream strs;
					std::string alltasks = "";
					//tasks concatenation
					for (auto& j : i->getTasks()) {
						//task - destination cross-checking
						if (j.getArgument(2) == destination) {
							//concatenate task
							alltasks += j.getArgument(1);
							alltasks += " ";
						}
					}
					//there is tasks to print
					if (alltasks.size() == 0) {
						alltasks = "no tasks.";
					}
					strs << " " << destination << ", " << alltasks;
					retval = strs.str();
				}
				//destination is coordinate
				else {
					std::ostringstream strs;
					strs << "(" << i->getDestinationX() << ", " << i->getDestinationY() << ")";
					retval = strs.str();
				}
				std::cout << CargoShipNameConvention << " " << *i << retval << std::endl;
			}
			else if (i->getStatus() == "Docked") {
				//if destination is a port
				if (getSeaPortByXY(i->getCurrentX(), i->getCurrentY()) != nullptr) {
					//his name
					destination = getSeaPortByXY(i->getDestinationX(), i->getDestinationY())->getName();
					std::ostringstream strs;
					strs << " at: " << destination;
					retval = strs.str();
				}
			}
			else {
				std::cout << CargoShipNameConvention << " " << *i << std::endl;
			}
		}
		//ship is not cargo ship
		else {
			std::cout << PirateShipNameConvention << " " << *i << std::endl;
		}
	}
}

SeaSimulatorModel* SeaSimulatorModel::inst = 0;

SeaSimulatorModel& SeaSimulatorModel::getInstance() {
	if (inst == 0)
		inst = new SeaSimulatorModel();
	return *inst;
}