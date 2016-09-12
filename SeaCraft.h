#ifndef SEACRAFT_H
#define SEACRAFT_H

#include "SeaObject.h"
#include "SeaMoveable.h"
#include "SeaTaskable.h"
#include <vector>

constexpr int MAX_SHIP_ARGS = 3;

class SeaCraft : public SeaObject, public SeaMoveable, public SeaTaskable {

	//print functions
	//to be implemented by derived classes (Ships) because each has its own specification
	virtual std::ostream& printCraft(std::ostream&)const = 0;
	//SeaCraft print method
	std::ostream& print(std::ostream& os) const;
	
protected:

	//arguments 
	std::vector<unsigned> craft_args;

	//status
	enum class StatusType { Stopped, Docked, Stuck, MovingTo , MovingOnCourse	}; // C++11 scoped enum
	//status type
	StatusType status;

public:

	SeaCraft(const std::string&, double, double);
	SeaCraft(const SeaCraft&) = delete;
	SeaCraft& operator= (const SeaCraft&) = delete;
	SeaCraft(SeaCraft&&) = delete;
	SeaCraft& operator= (const SeaCraft&&) = delete;
	virtual ~SeaCraft() = 0;

	void setStatus(const std::string&);
	const std::string getStatus();

};



#endif