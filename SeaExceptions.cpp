#include "SeaExceptions.h"

//Model exceptions

SeaObjectNotFound::SeaObjectNotFound(const std::string& _which):which(_which) {

	std::ostringstream cnvr;
	cnvr.str("");
	cnvr << "Object " << which << " not found.";
	which = cnvr.str();

}

const char* SeaObjectNotFound::what() const throw() {

	return which.c_str();

}


//Controller exceptions

FileNotFound::FileNotFound(const std::string& _which) :which(_which) {
	std::ostringstream cnvr;
	cnvr.str("");
	cnvr << "File " << which << " not found.";
	which = cnvr.str();
}

const char* FileNotFound::what() const throw() {

	return which.c_str();

}

FileCorrupted::FileCorrupted(const std::string& _which) :which(_which) {

	std::ostringstream cnvr;
	cnvr.str("");
	cnvr << "File " << which << " corrupted.";
	which = cnvr.str();

}

const char* FileCorrupted::what() const throw() {

	return which.c_str();

}

BadArguments::BadArguments(const std::string& _which) :which(_which) {

	std::ostringstream cnvr;
	cnvr.str("");
	cnvr << "Invalid input " << which;
	which = cnvr.str();
}

const char* BadArguments::what() const throw() {

	return which.c_str();
}
