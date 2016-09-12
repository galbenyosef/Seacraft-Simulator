#include "SeaSimulatorController.h"

SeaSimulatorController::SeaSimulatorController(SeaSimulatorModel& _model, std::shared_ptr<SeaSimulatorView> _view) :model(_model), view(_view) {}

void SeaSimulatorController::start(char filename[]) {

	try {
		readFile(filename);
		getCommandsPhrase();
	}
	catch (const std::exception& ex) {
		std::cerr << ex.what() << std::endl;
	}

}

void SeaSimulatorController::readFile(char filename[]) {
	std::ifstream fileToRead(filename);
	if (!fileToRead.is_open())
		throw FileNotFound(filename);
	std::string line;
	//while file has lines to read
	while (std::getline(fileToRead, line))
	{
		std::string fixedline;
		//ignoring '(' , ')' , ','
		fixedline.reserve(line.size() - 3);
		for (size_t i = 0; i < line.size(); ++i) {
			if (line[i] != '(' && line[i] != ')' && line[i] != ',') fixedline += line[i];
		}

		//using isstream extraction
		std::istringstream iss(fixedline);
		std::string name;
		double x, y;
		unsigned fuel_cap, fuel_prod;

		if (!(iss >> name >> x >> y >> fuel_cap >> fuel_prod)) {
			throw FileCorrupted(filename);
		} // error

		model.add(SeaObjectMaker<SeaPort>::make(name, x, y, fuel_cap, fuel_prod));
	}
}

void SeaSimulatorController::getCommandsPhrase() {

	std::string line;

	while (true) {
		try {
			std::cout << "Time: " << model.getTimer() << " Enter Command: ";
			std::getline(std::cin, line);
			SeaSimulatorCommand command(line);
			
			//invalid line exception
			if (!command.isValid()) {
				std::string badline;
				for (size_t i = 0; i < MAX_ARGUMENTS; i++) {
					if (command.getArgument(i) != "None") {
						badline += command.getArgument(i);
						badline += " ";
					}
				}
				throw BadArguments(badline);
			}

			//instant command should be executed immediately
			if (command.getName() == "quit") {
				break;
			}
			else if (command.getName() == "go") {
				if (!commands_on_hold.empty()) {
					readCommandsPhrase();
				}
				model.update();
			}
			else if (command.getName() == "show") {
				view->DrawASCII(model);
			}
			else if (command.getName() == "pan") {
				view->setOrigin(std::stoi(command.getArgument(1)), std::stoi(command.getArgument(2)));
			}
			else if (command.getName() == "zoom") {
				view->setScale(std::stoi(command.getArgument(1)));
			}
			else if (command.getName() == "size") {
				view->setSize(std::stoi(command.getArgument(1)));
			}
			else if (command.getName() == "default") {
				view->reset();
			}
			else if (command.getName() == "status") {
				model.status();
			}
			//suppose any ship object init'ed by six arguments
			else if (command.getName() == "create") {
				//arguments
				std::string craft_name, craft_type;
				double x, y;
				unsigned arg1, arg2;
				//fetch arguments
				craft_name = command.getArgument(1);
				craft_type = command.getArgument(2);
				x = std::stod(command.getArgument(3));
				y = std::stod(command.getArgument(4));
				arg1 = std::stoul(command.getArgument(5));
				arg2 = std::stoul(command.getArgument(6));
				//SeaObjectMaker to create Ships
				if (craft_type == PirateShipNameConvention) {
					//add to model
					model.add(SeaObjectMaker<PirateShip>::make(craft_name, x, y, arg1, arg2));
				}
				if (craft_type == CargoShipNameConvention) {
					model.add(SeaObjectMaker<CargoShip>::make(craft_name, x, y, arg2, arg1));
				}
			}
			//wait to 'go' commands are on hold
			//command is valid and not one of above
			else
				commands_on_hold.push(command);
		}
		catch (const std::exception& ex) {

			std::cout << ex.what() << std::endl;
			continue;

		}
	}
}

void SeaSimulatorController::getCommandsPhraseFile(char filename[]) {
	std::ifstream fileToRead(filename);
	std::string line;
	int time = 0;

	while (true) {

		std::cout << "Press any key to continue...\n";
		std::getline(fileToRead, line);
		SeaSimulatorCommand command(line);

		if (command.isValid()) {

			//instant command should be executed immediately
			if (command.getName() == "quit") {
				break;
			}
			else if (command.getName() == "go") {
				if (!commands_on_hold.empty()) {
					readCommandsPhrase();
				}
				model.update();
				time++;
			}
			else if (command.getName() == "show") {
				view->DrawASCII(model);
			}
			else if (command.getName() == "pan") {
				view->setOrigin(std::stoi(command.getArgument(1)), std::stoi(command.getArgument(2)));
			}
			else if (command.getName() == "zoom") {
				view->setScale(std::stoi(command.getArgument(1)));
			}
			else if (command.getName() == "size") {
				view->setSize(std::stoi(command.getArgument(1)));
			}
			else if (command.getName() == "default") {
				view->reset();
			}
			else if (command.getName() == "status") {
				model.status();
			}
			//suppose any ship object init'ed by six arguments
			else if (command.getName() == "create") {
				//arguments
				std::string craft_name, craft_type;
				double x, y;
				unsigned arg1, arg2;
				//fetch arguments
				craft_name = command.getArgument(1);
				craft_type = command.getArgument(2);
				x = std::stod(command.getArgument(3));
				y = std::stod(command.getArgument(4));
				arg1 = std::stoul(command.getArgument(5));
				arg2 = std::stoul(command.getArgument(6));
				//SeaObjectMaker to create Ships
				if (craft_type == PirateShipNameConvention) {
					//add to model
					model.add(SeaObjectMaker<PirateShip>::make(craft_name, x, y, arg1, arg2));
				}
				if (craft_type == CargoShipNameConvention) {
					model.add(SeaObjectMaker<CargoShip>::make(craft_name, x, y, arg2, arg1));
				}

			}
			//wait to 'go' commands are queued
			else {
				commands_on_hold.push(command);
			}
			getchar();
		}
	}
}

void SeaSimulatorController::readCommandsPhrase() {

	//todo curx cury get from model after craft name

	do {
		//fetch command
		SeaSimulatorCommand valid_command(commands_on_hold.front());
		//execute
		std::string craft_name = valid_command.getArgument(0);
		//polar direction movement
		if (valid_command.getName() == "course") {

			double thetha = std::stod(valid_command.getArgument(2));
			double speed = std::stod(valid_command.getArgument(3));

			model.getInstance().getSeaCraftByName(craft_name)->moveTo(thetha, speed);
			model.getInstance().getSeaCraftByName(craft_name)->setStatus("MovingOnCourse");
		}

		//cartesian destination movement
		else if (valid_command.getName() == "position" || valid_command.getName() == "destination") {

			double curx, cury, dstx, dsty, speed;

			curx = model.getInstance().getSeaCraftByName(craft_name)->getX();
			cury = model.getInstance().getSeaCraftByName(craft_name)->getY();

			if (valid_command.getName() == "position") {
				dstx = std::stod(valid_command.getArgument(2));
				dsty = std::stod(valid_command.getArgument(3));
				speed = std::stod(valid_command.getArgument(4));;
			}
			else {
				std::string destination = valid_command.getArgument(2);
				dstx = SeaSimulatorModel::getInstance().getSeaPortByName(destination)->getX();
				dsty = SeaSimulatorModel::getInstance().getSeaPortByName(destination)->getY();
				speed = std::stod(valid_command.getArgument(3));
			}

			model.getInstance().getSeaCraftByName(craft_name)->navigateTo(curx, cury, dstx, dsty, speed);
			model.getInstance().getSeaCraftByName(craft_name)->setStatus("MovingTo");

		}

		//in-place ship commands which have to be executed while source has reach his destination
		else if (valid_command.getName() == "attack") {

			std::string target_name = valid_command.getArgument(2);
			double fromX, fromY, toX, toY, distance;
			unsigned range, resistance;

			fromX = model.getInstance().getSeaCraftByName(craft_name)->getX();
			fromY = model.getInstance().getSeaCraftByName(craft_name)->getY();
			toX = model.getInstance().getSeaCraftByName(target_name)->getX();
			toY = model.getInstance().getSeaCraftByName(target_name)->getY();

			std::shared_ptr<SeaCraft> source, target;
			distance = distanceCalculate(fromX, fromY, toX, toY);
			source = model.getInstance().getSeaCraftByName(craft_name);
			target = model.getInstance().getSeaCraftByName(target_name);

			std::shared_ptr<PirateShip> source_morph = std::static_pointer_cast<PirateShip>(source);
			std::shared_ptr<CargoShip> target_morph = std::static_pointer_cast<CargoShip>(target);

			range = source_morph->getRange();
			resistance = target_morph->getResistance();

			if (distance <= (double)range) {

				bool raidSuccess = source_morph->attack(resistance);
				//pirates win, cargo lose
				if (raidSuccess) {

					target_morph->setLoser();

				}
				//pirate lose, cargo win
				else {

					source_morph->setLoser();

				}
			}
		}
		else if (valid_command.getName() == "refuel") {

			double curx, cury;
			unsigned incoming_fuel;

			curx = model.getInstance().getSeaCraftByName(craft_name)->getX();
			cury = model.getInstance().getSeaCraftByName(craft_name)->getY();

			std::shared_ptr<SeaCraft> tempcraft;
			if ((tempcraft = model.getInstance().getSeaCraftByName(craft_name))->hasReachedDestination()) {
				std::shared_ptr<SeaPort> temport;
				if ((temport = model.getInstance().getSeaPortByXY(curx, cury)) != nullptr) {
					incoming_fuel = temport->getFuelCapacity();
					temport->decFuel((std::static_pointer_cast<CargoShip>(tempcraft))->refuel(incoming_fuel));
				}
			}



		}

		//stop
		else if (valid_command.getName() == "stop") {

			model.getInstance().getSeaCraftByName(craft_name)->stop();
			model.getInstance().getSeaCraftByName(craft_name)->setStatus("Stopped");
		}

		//wait to go commands which have to be 'tasked'
		else if (valid_command.getName() == "load_at" || valid_command.getName() == "unload_at" || valid_command.getName() == "dock_at") {

			model.getInstance().getSeaCraftByName(craft_name)->task(valid_command);

		}

		commands_on_hold.pop();

	} while (!commands_on_hold.empty());
}

SeaSimulatorController* SeaSimulatorController::inst = 0;

SeaSimulatorController& SeaSimulatorController::getInstance() {
	if (inst == 0) {
		std::shared_ptr<SeaSimulatorView> view(new SeaSimulatorView());
		inst = new SeaSimulatorController(SeaSimulatorModel::getInstance(), view);
	}
	return *inst;
}
