#pragma once
#include "Service.h"

class Console {
	// class that will handle user interaction and parameter validation
	private:
		Service& serv;
		void handleAdd();
		void handleDischarge();
		void handleUpdate();
		void handleShow();
		void handleSurgeries();
		void handleConsults();
		void handleShowSurgeries();
		void handleShowConsults();
		void printMenu();
		// we keep all these internal functions private such that only this class can access them
	public:
		Console(Service& serv) : serv(serv) {};
		~Console() {};
		void run();
};