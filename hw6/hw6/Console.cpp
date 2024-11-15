#include "Console.h"

void Console::printMenu() {
	std::cout << std::endl;
	std::cout << "1. Animals menu" << std::endl;
	std::cout << "2. Cages menu" << std::endl;
	std::cout << "3. Supervisors menu" << std::endl;
	std::cout << "4. Management menu" << std::endl;
	std::cout << "5. Exit" << std::endl << std::endl;
}

void Console::handleAnimal() {
	std::cout << std::endl;
	std::cout << "1. Add animal" << std::endl;
	std::cout << "2. Update animal" << std::endl;
	std::cout << "3. Remove animal" << std::endl;
	std::cout << "4. Show an animal" << std::endl;
	std::cout << "5. Show all animals" << std::endl << std::endl;

	int option;
	std::cout << "Enter option: "; std::cin >> option;

	switch (option) {
		case 1: {
			int cageID;
			std::string name, race;
			float height, weight;

			std::cout << std::endl << "Cage ID: "; std::cin >> cageID;
			std::cin.ignore();
			std::cout << "Name: "; std::getline(std::cin, name);
			std::cout << "Race: "; std::getline(std::cin, race);
			std::cout << "Height: "; std::cin >> height;
			std::cout << "Weight: "; std::cin >> weight;

			bool res = this->s.addAnimal(cageID, name, race, height, weight);
			if (res)
				std::cout << std::endl << "Animal added successfully!" << std::endl << std::endl;
			else
				std::cout << std::endl << "Animal not added due to various issues! Try again." << std::endl << std::endl;
			break;
		}
		case 2: {
			int ID, cageID;
			std::string name, race;
			float height, weight;

			std::cout << std::endl << "ID: "; std::cin >> ID;
			std::cout << "Cage ID: "; std::cin >> cageID;
			std::cin.ignore();
			std::cout << "Name: "; std::getline(std::cin, name);
			std::cout << "Race: "; std::getline(std::cin, race);
			std::cout << "Height: "; std::cin >> height;
			std::cout << "Weight: "; std::cin >> weight;


			bool res = this->s.updateAnimal(ID, cageID, name, race, height, weight);

			if (res)
				std::cout << std::endl << "Animal update successfully!" << std::endl << std::endl;
			else
				std::cout << std::endl << "Animal not updated due to various issues! Try again." << std::endl << std::endl;
			break;
		}
		case 3: {
			int ID;

			std::cout << std::endl << "ID: "; std::cin >> ID;

			bool res = this->s.deleteAnimal(ID);
			if (res)
				std::cout << std::endl << "Animal deleted successfully!" << std::endl << std::endl;
			else
				std::cout << std::endl << "Animal doesn't exist! Try again." << std::endl << std::endl;
			break;

		}
		case 4: {
			int ID;

			std::cout << std::endl << "ID: "; std::cin >> ID;

			Animal* elem = this->s.readAnimal(ID);

			if (elem == nullptr)
				std::cout << std::endl << "Animal doesn't exist! Try again." << std::endl << std::endl;
			else
				elem->print();
			break;
		}
		case 5: {
			Animal** animals = this->s.getAllAnimals();
			int size = this->s.getAnimalsSize();

			for (int i = 0; i < size; i++)
				animals[i]->print();
			break;
		}
		default: {
			std::cout << std::endl << "Wrong option! Try again." << std::endl << std::endl;
			break;
		}
	}
}

void Console::handleCage() {
	std::cout << std::endl;
	std::cout << "1. Add cage" << std::endl;
	std::cout << "2. Update cage" << std::endl;
	std::cout << "3. Remove cage" << std::endl;
	std::cout << "4. Show a cage" << std::endl;
	std::cout << "5. Show all cages" << std::endl << std::endl;

	int option;
	std::cout << "Enter option: "; std::cin >> option;

	switch (option) {
		case 1: {
			int supervisorID, noAnimals;
			int animalIDs[10]; // initialize all elements with -1
			for (int i = 0; i < 10; i++)
				animalIDs[i] = -1;

			std::cout << std::endl << "Supervisor ID: "; std::cin >> supervisorID;
			std::cout << "Number of animals (max 10): "; std::cin >> noAnimals;

			if (noAnimals < 0 || noAnimals > 10) {
				std::cout << std::endl << "Number of animals is incorrect! Try again." << std::endl << std::endl;
				return;
			}

			for (int i = 0; i < noAnimals; i++) {
				std::cout << "Animal " << i + 1 << " ID: "; std::cin >> animalIDs[i];
			}

			bool res = this->s.addCage(supervisorID, animalIDs);
			if (res)
				std::cout << std::endl << "Cage added successfully!" << std::endl << std::endl;
			else
				std::cout << std::endl << "Cage couldn't be added! Try again." << std::endl << std::endl;
			break;
		}
		case 2: {
			int ID, supervisorID, noAnimals;
			int animalIDs[10] = { -1 }; // initialize all elements with -1

			std::cout << std::endl << "ID: "; std::cin >> ID;
			std::cout << "Supervisor ID: "; std::cin >> supervisorID;
			std::cout << "Number of animals (max 10): "; std::cin >> noAnimals;

			if (noAnimals < 0 || noAnimals > 10) {
				std::cout << std::endl << "Number of animals is incorrect! Try again." << std::endl << std::endl;
				return;
			}

			for (int i = 0; i < noAnimals; i++) {
				std::cout << "Animal " << i + 1 << " ID: "; std::cin >> animalIDs[i];
			}

			bool res = this->s.updateCage(ID, supervisorID, animalIDs);
			if (res)
				std::cout << std::endl << "Cage updated successfully!" << std::endl << std::endl;
			else
				std::cout << std::endl << "Cage couldn't be updated! Try again." << std::endl << std::endl;
			break;
		}
		case 3: {
			int ID;

			std::cout << std::endl << "ID: "; std::cin >> ID;

			bool res = this->s.deleteCage(ID);
			if (res)
				std::cout << std::endl << "Cage deleted successfully!" << std::endl << std::endl;
			else
				std::cout << std::endl << "Cage doesn't exist! Try again." << std::endl << std::endl;
			break;

		}
		case 4: {
			int ID;

			std::cout << std::endl << "ID: "; std::cin >> ID;

			Cage* elem = this->s.readCage(ID);

			if (elem == nullptr)
				std::cout << std::endl << "Cage doesn't exist! Try again." << std::endl << std::endl;
			else
				elem->print();
			break;
		}
		case 5: {
			Cage** cages = this->s.getAllCages();
			int size = this->s.getCagesSize();

			for (int i = 0; i < size; i++)
				cages[i]->print();
			break;
		}
		default: {
			std::cout << std::endl << "Wrong option! Try again." << std::endl << std::endl;
			break;
		}
	}
}

void Console::handleSupervisor() {
	std::cout << std::endl;
	std::cout << "1. Add supervisor" << std::endl;
	std::cout << "2. Update supervisor" << std::endl;
	std::cout << "3. Remove supervisor" << std::endl;
	std::cout << "4. Show a supervisor" << std::endl;
	std::cout << "5. Show all supervisors" << std::endl << std::endl;

	int option;
	std::cout << "Enter option: "; std::cin >> option;

	switch (option) {
		case 1: {
			int cageID;
			std::string name;

			std::cout << std::endl << "Cage ID: "; std::cin >> cageID;
			std::cin.ignore();
			std::cout << "Name: "; std::getline(std::cin, name);

			bool res = this->s.addSupervisor(name, cageID);
			if (res)
				std::cout << std::endl << "Supervisor added successfully!" << std::endl << std::endl;
			else
				std::cout << std::endl << "Supervisor couldn't be added! Try again." << std::endl << std::endl;
			break;
		}
		case 2: {
			int ID, cageID;
			std::string name;

			std::cout << std::endl << "ID: "; std::cin >> ID;
			std::cout << "Cage ID: "; std::cin >> cageID;
			std::cin.ignore();
			std::cout << "Name: "; std::getline(std::cin, name);

			bool res = this->s.updateSupervisor(ID, name, cageID);
			if (res)
				std::cout << std::endl << "Supervisor updated successfully!" << std::endl << std::endl;
			else
				std::cout << std::endl << "Supervisor couldn't be updated! Try again." << std::endl << std::endl;
			break;
		}
		case 3: {
			int ID;

			std::cout << std::endl << "ID: "; std::cin >> ID;

			bool res = this->s.deleteSupervisor(ID);
			if (res)
				std::cout << std::endl << "Supervisor deleted successfully!" << std::endl << std::endl;
			else
				std::cout << std::endl << "Supervisor doesn't exist! Try again." << std::endl << std::endl;
			break;

		}
		case 4: {
			int ID;

			std::cout << std::endl << "ID: "; std::cin >> ID;

			Supervisor* elem = this->s.readSupervisor(ID);

			if (elem == nullptr)
				std::cout << std::endl << "Supervisor doesn't exist! Try again." << std::endl << std::endl;
			else
				elem->print();
			break;
		}
		case 5: {
			Supervisor** supervisors = this->s.getAllSupervisors();
			int size = this->s.getSupervisorsSize();

			for (int i = 0; i < size; i++)
				supervisors[i]->print();
			break;
		}
		default: {
			std::cout << std::endl << "Wrong option! Try again." << std::endl << std::endl;
			break;
		}
	}
}

void Console::handleManagement() {
	std::cout << std::endl;
	std::cout << "1. Add animal to cage" << std::endl;
	std::cout << "2. Remove animal from cage" << std::endl;
	std::cout << "3. Add supervisor to cage" << std::endl;
	std::cout << "4. Remove supervisor from cage" << std::endl << std::endl;

	int option;
	std::cout << "Enter option: "; std::cin >> option;

	switch (option) {
		case 1: {
			int animalID, cageID;

			std::cout << std::endl << "Animal ID: "; std::cin >> animalID;
			std::cout << "Cage ID: "; std::cin >> cageID;

			bool res = this->s.assignAnimalToCage(animalID, cageID);
			if (res)
				std::cout << std::endl << "Animal added successfully to cage!" << std::endl << std::endl;
			else
				std::cout << std::endl << "Either animal or cage don't exist! Try again." << std::endl << std::endl;
			break;
		}
		case 2: {
			int animalID, cageID;

			std::cout << std::endl << "Animal ID: "; std::cin >> animalID;
			std::cout << "Cage ID: "; std::cin >> cageID;

			bool res = this->s.removeAnimalFromCage(animalID, cageID);
			if (res)
				std::cout << std::endl << "Animal removed successfully from cage!" << std::endl << std::endl;
			else
				std::cout << std::endl << "Either animal or cage don't exist! Try again." << std::endl << std::endl;
			break;
		}
		case 3: {
			int supervisorID, cageID;

			std::cout << std::endl << "Supervisor ID: "; std::cin >> supervisorID;
			std::cout << "Cage ID: "; std::cin >> cageID;

			bool res = this->s.assignSupervisorToCage(supervisorID, cageID);
			if (res)
				std::cout << std::endl << "Supervisor added successfully to cage!" << std::endl << std::endl;
			else
				std::cout << std::endl << "Either supervisor or cage don't exist! Try again." << std::endl << std::endl;
			break;
		}
		case 4: {
			int supervisorID, cageID;

			std::cout << std::endl << "Supervisor ID: "; std::cin >> supervisorID;
			std::cout << "Cage ID: "; std::cin >> cageID;

			bool res = this->s.removeSupervisorFromCage(supervisorID, cageID);
			if (res)
				std::cout << std::endl << "Supervisor removed successfully from cage!" << std::endl << std::endl;
			else
				std::cout << std::endl << "Either supervisor or cage don't exist! Try again." << std::endl << std::endl;
			break;
		}
		default: {
			std::cout << std::endl << "Wrong option! Try again." << std::endl << std::endl;
			break;
		}
	}
}

void Console::run() {
	this->printMenu();

	int option;
	std::cout << "Enter option: "; std::cin >> option;
	while (true) {
		switch (option) {
			case 1: {
				this->handleAnimal();
				break;
			}
			case 2: {
				this->handleCage();
				break;
			}
			case 3: {
				this->handleSupervisor();
				break;
			}
			case 4: {
				this->handleManagement();
				break;
			}
			case 5: {
				std::cout << std::endl << "Goodbye!" << std::endl;
				return;
			}
			default: {
				std::cout << std::endl << "Wrong option! Try again." << std::endl << std::endl;
				break;
			}
		}

		this->printMenu();
		std::cout << "Enter option: "; std::cin >> option;
	}
	
}