simNautica: main.o CargoShip.o PirateShip.o SeaCraft.o SeaExceptions.o \
 SeaMoveable.o SeaObject.o SeaPort.o SeaSimulatorCommand.o SeaSimulatorController.o \
 SeaSimulatorModel.o SeaSimulatorView.o SeaTaskable.o
	g++ -std=c++11 -W -Wall -pedantic -Werror -Wextra main.o CargoShip.o PirateShip.o SeaCraft.o SeaExceptions.o SeaMoveable.o SeaObject.o SeaPort.o SeaSimulatorCommand.o SeaSimulatorController.o SeaSimulatorModel.o SeaSimulatorView.o SeaTaskable.o -o simNautica
CargoShip.o: CargoShip.cpp CargoShip.h SeaCraft.h SeaObject.h \
 SeaMoveable.h SeaTaskable.h SeaSimulatorCommand.h
	g++ -std=c++11 -W -Wall -pedantic -Werror -Wextra -c CargoShip.cpp
main.o: main.cpp SeaSimulatorController.h SeaSimulatorModel.h \
 SeaExceptions.h SeaCraft.h SeaObject.h SeaMoveable.h SeaTaskable.h \
 SeaSimulatorCommand.h SeaPort.h CargoShip.h PirateShip.h \
 SeaSimulatorView.h SeaObjectMaker.h
	g++ -std=c++11 -W -Wall -pedantic -Werror -Wextra -c main.cpp
PirateShip.o: PirateShip.cpp PirateShip.h SeaCraft.h SeaObject.h \
 SeaMoveable.h SeaTaskable.h SeaSimulatorCommand.h
	g++ -std=c++11 -W -Wall -pedantic -Werror -Wextra -c PirateShip.cpp
SeaCraft.o: SeaCraft.cpp SeaCraft.h SeaObject.h SeaMoveable.h \
 SeaTaskable.h SeaSimulatorCommand.h
	g++ -std=c++11 -W -Wall -pedantic -Werror -Wextra -c SeaCraft.cpp
SeaExceptions.o: SeaExceptions.cpp SeaExceptions.h
	g++ -std=c++11 -W -Wall -pedantic -Werror -Wextra -c SeaExceptions.cpp
SeaMoveable.o: SeaMoveable.cpp SeaMoveable.h
	g++ -std=c++11 -W -Wall -pedantic -Werror -Wextra -c SeaMoveable.cpp
SeaObject.o: SeaObject.cpp SeaObject.h
	g++ -std=c++11 -W -Wall -pedantic -Werror -Wextra -c SeaObject.cpp
SeaPort.o: SeaPort.cpp SeaPort.h SeaObject.h
	g++ -std=c++11 -W -Wall -pedantic -Werror -Wextra -c SeaPort.cpp
SeaSimulatorCommand.o: SeaSimulatorCommand.cpp SeaSimulatorCommand.h
	g++ -std=c++11 -W -Wall -pedantic -Werror -Wextra -c SeaSimulatorCommand.cpp
SeaSimulatorController.o: SeaSimulatorController.cpp \
 SeaSimulatorController.h SeaSimulatorModel.h SeaExceptions.h SeaCraft.h \
 SeaObject.h SeaMoveable.h SeaTaskable.h SeaSimulatorCommand.h SeaPort.h \
 CargoShip.h PirateShip.h SeaSimulatorView.h SeaObjectMaker.h
	g++ -std=c++11 -W -Wall -pedantic -Werror -Wextra -c SeaSimulatorController.cpp
SeaSimulatorModel.o: SeaSimulatorModel.cpp SeaSimulatorModel.h \
 SeaExceptions.h SeaCraft.h SeaObject.h SeaMoveable.h SeaTaskable.h \
 SeaSimulatorCommand.h SeaPort.h CargoShip.h PirateShip.h
	g++ -std=c++11 -W -Wall -pedantic -Werror -Wextra -c SeaSimulatorModel.cpp
SeaSimulatorView.o: SeaSimulatorView.cpp SeaSimulatorView.h \
 SeaSimulatorModel.h SeaExceptions.h SeaCraft.h SeaObject.h SeaMoveable.h \
 SeaTaskable.h SeaSimulatorCommand.h SeaPort.h CargoShip.h PirateShip.h
	g++ -std=c++11 -W -Wall -pedantic -Werror -Wextra -c SeaSimulatorView.cpp
SeaTaskable.o: SeaTaskable.cpp SeaTaskable.h SeaSimulatorCommand.h
	g++ -std=c++11 -W -Wall -pedantic -Werror -Wextra -c SeaTaskable.cpp