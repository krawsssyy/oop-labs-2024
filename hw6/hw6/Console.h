#pragma once
#include "Service.h"

class Console {
private:
	Service& s;
	void printMenu();
	void handleAnimal();
	void handleCage();
	void handleSupervisor();
	void handleManagement();
public:
	Console() = default;
	Console(Service& s) : s(s) {}
	~Console() {}
	void run();
};