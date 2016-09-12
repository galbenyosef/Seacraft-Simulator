#include "SeaCraft.h"

std::ostream& SeaCraft::print(std::ostream& os) const {
	std::string StatusToString;

	switch (status) {
	case StatusType::MovingOnCourse:
		StatusToString = "Moving on course";
		break;
	case StatusType::Docked:
		StatusToString = "Docked at";
		break;
	case StatusType::MovingTo:
		StatusToString = "Moving to";
		break;
	case StatusType::Stopped:
		StatusToString = "Stopped";
		break;
	case StatusType::Stuck:
		StatusToString = "Dead on the water";
		break;
	}
	printCraft(os);
	//rad to deg
	double degree = getAngle() * 180 / PI;
	if (degree >= 0 && degree <= 90) {
		degree = 90 - degree;
	}
	else {
		degree = 450 - degree;
	}
	return os << "Degree: " << degree << ", Speed: " << std::setprecision(2) << std::fixed << getSpeed() << " nm/hr. " << StatusToString;
}

SeaCraft::SeaCraft(const std::string& new_name, double x_pos, double y_pos)
	: SeaObject(new_name, x_pos, y_pos), SeaMoveable(x_pos, y_pos), craft_args(MAX_SHIP_ARGS) {
	status = StatusType::Stopped;
}

void SeaCraft::setStatus(const std::string& stat) {

	if (stat == "Stopped")
		status = StatusType::Stopped;
	else if (stat == "Docked")
		status = StatusType::Docked;
	else if (stat == "Stuck")
		status = StatusType::Stuck;
	else if (stat == "MovingTo")
		status = StatusType::MovingTo;
	else if (stat == "MovingOnCourse")
		status = StatusType::MovingOnCourse;

}

const std::string SeaCraft::getStatus() {

	if (status == StatusType::Stopped)
		return "Stopped";
	else if (status == StatusType::Docked)
		return "Docked";
	else if (status == StatusType::Stuck)
		return "Stuck";
	else if (status == StatusType::MovingTo)
		return "MovingTo";
	else if (status == StatusType::MovingOnCourse)
		return "MovingOnCourse";
	else
		return "NOSTATUS";
}

SeaCraft::~SeaCraft() {}