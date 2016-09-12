#include <exception>
#include <string>
#include <sstream>
#include <iostream>

class SeaObjectNotFound : public std::exception{

	std::string which;

public:
	SeaObjectNotFound(const std::string&);
	virtual const char* what() const throw();
	
};

class FileNotFound : public std::exception {

	std::string which;

public:

	FileNotFound(const std::string&);
	virtual const char* what() const throw();

};

class FileCorrupted : public std::exception {

	std::string which;

public:

	FileCorrupted(const std::string&);
	virtual const char* what() const throw();

};

class BadArguments : public std::exception {

	std::string which;

public:

	BadArguments(const std::string&);
	virtual const char* what() const throw();

};

