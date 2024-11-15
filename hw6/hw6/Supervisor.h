#pragma once
#include <string>
#include <iostream>

class Supervisor {
private:
	inline static int counter = 0; // using "inline" so we can define the counter statically in the header file
	// else, if we used a cpp file, we would do int Supervisor::counter = 0 to initialize it
	// inline keyword
	// it makes variables have static-type storage across all definitions
	// due to multiple inclusions of the header file and the inclusions of it, where the initialization was, it would have been redefined multiple times, which is a violation of ODR (one-definition-rule)
	// inline helps prevent that
	// requires c++17 or higher
	int id;
	std::string name;
	int cageID;
public:
	Supervisor() = default;
	Supervisor(std::string name, int cageID) : id(counter++), name(name), cageID(cageID) {}
	~Supervisor() {}
	int getID() { return this->id; }
	std::string getName() { return this->name; }
	void setName(std::string name) { this->name = name; }
	int getCageID() { return this->cageID; }
	void setCageID(int cageID) { this->cageID = cageID; }

	void print() {
		std::cout << std::endl << "Supervisor" << std::endl << "Name: " << this->name << std::endl
			<< "Cage ID: " << this->cageID << std::endl << std::endl;
	}

};
