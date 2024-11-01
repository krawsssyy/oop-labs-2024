#include "Console.h"

void Console::handleAdd() {
	std::string name, CNP, diagnosis;
	int age, noSurgeries, noConsults;

	std::cin.ignore();
	std::cout << "Enter patient's name: "; std::getline(std::cin, name);
	std::cout << "Enter patient's CNP: "; std::getline(std::cin, CNP);
	std::cout << "Enter patient's diagnosis: "; std::getline(std::cin, diagnosis);
	std::cout << "Enter patient's age: "; std::cin >> age;
	std::cout << "Enter the amount of surgeries the patient had: "; std::cin >> noSurgeries;
	std::cout << "Enter the amount of consults the patient had: "; std::cin >> noConsults;

	if (age < 0 || age > 130) { // small parameters checks
		std::cout << std::endl << "Invalid age!" << std::endl << std::endl;
		return;
	}

	if (CNP.length() != 13) {
		std::cout << std::endl <<  "Invalid CNP!" << std::endl << std::endl;
		return;
	}
	
	Pair *surgeries = nullptr, *consults = nullptr;

	if (noSurgeries > 0)
		surgeries = new Pair[noSurgeries];

	if (noConsults > 0)
		consults = new Pair[noConsults];

	std::cin.ignore();
	std::cout << std::endl;

	for (int i = 0; i < noSurgeries; i++) {
		std::string surgery, date;
		std::cout << "Enter surgery type for surgery " << i + 1 << ": "; std::getline(std::cin, surgery);
		std::cout << "Enter surgery date for surgery " << i + 1 << ": "; std::getline(std::cin, date);
		Pair surgeryPair(surgery, date);
		surgeries[i] = surgeryPair;
	}

	for (int i = 0; i < noConsults; i++) {
		std::string consult, date;
		std::cout << "Enter consult type for consult " << i + 1 << ": "; std::getline(std::cin, consult);
		std::cout << "Enter consult date for consult " << i + 1 << ": "; std::getline(std::cin, date);
		Pair consultPair(consult, date);
		consults[i] = consultPair;
	}

	this->serv.addPatient(name, CNP, age, diagnosis, surgeries, noSurgeries, consults, noConsults);

	std::cout << std::endl <<"Added patient!" << std::endl << std::endl;
}

void Console::handleDischarge() {
	int option;

	std::cout << "1. Mark patient as healed and discharge" << std::endl;
	std::cout << "2. Mark patient as dead and discharge" << std::endl;
	std::cout << "3. Discharge patient at his request" << std::endl;

	std::cout << "Enter option: "; std::cin >> option;
	std::cout << std::endl;

	if (option != 1 && option != 2 && option != 3) {
		std::cout << std::endl << "Invalid option!" << std::endl << std::endl;
		return;
	}

	std::string CNP;

	std::cin.ignore();
	std::cout << "Enter patient's CNP: "; std::getline(std::cin, CNP);

	if (option == 1) {
		bool result = this->serv.markAsHealed(CNP);
		if (result == true)
			std::cout << std::endl << "Patient successfully discharged!" << std::endl << std::endl;
		else
			std::cout << std::endl << "Invalid CNP!" << std::endl << std::endl;
	}
	else {
		bool result = this->serv.deletePatient(CNP);
		if (result == true)
			std::cout << std::endl << "Patient successfully discharged!" << std::endl << std::endl;
		else
			std::cout << std::endl << "Invalid CNP!" << std::endl << std::endl;
	}

}

void Console::handleUpdate() {
	std::string name, CNP, diagnosis, origCNP;
	int age, noSurgeries, noConsults;

	std::cin.ignore();
	std::cout << "Enter patient's original CNP: "; std::getline(std::cin, origCNP);
	std::cout << "Enter patient's new name: "; std::getline(std::cin, name);
	std::cout << "Enter patient's new CNP: "; std::getline(std::cin, CNP);
	std::cout << "Enter patient's new diagnosis: "; std::getline(std::cin, diagnosis);
	std::cout << "Enter patient's new age: "; std::cin >> age;
	std::cout << "Enter the new amount of surgeries the patient had: "; std::cin >> noSurgeries;
	std::cout << "Enter the new amount of consults the patient had: "; std::cin >> noConsults;

	if (age < 0 || age > 130) { // small parameters checks
		std::cout << std::endl << "Invalid age!" << std::endl << std::endl;
		return;
	}

	if (CNP.length() != 13) {
		std::cout << std::endl << "Invalid CNP!" << std::endl << std::endl;
		return;
	}

	Pair *surgeries = nullptr, *consults = nullptr;

	if (noSurgeries > 0)
		surgeries = new Pair[noSurgeries];

	if (noConsults > 0)
		consults = new Pair[noConsults];

	std::cin.ignore();
	std::cout << std::endl;

	for (int i = 0; i < noSurgeries; i++) {
		std::string surgery, date;
		std::cout << "Enter surgery type for surgery " << i + 1 << ": "; std::getline(std::cin, surgery);
		std::cout << "Enter surgery date for surgery " << i + 1 << ": "; std::getline(std::cin, date);
		Pair surgeryPair(surgery, date);
		surgeries[i] = surgeryPair;
	}

	for (int i = 0; i < noConsults; i++) {
		std::string consult, date;
		std::cout << "Enter consult type for consult " << i + 1 << ": "; std::getline(std::cin, consult);
		std::cout << "Enter consult date for consult " << i + 1 << ": "; std::getline(std::cin, date);
		Pair consultPair(consult, date);
		consults[i] = consultPair;
	}

	this->serv.updatePatient(origCNP, name, CNP, age, diagnosis, surgeries, noSurgeries, consults, noConsults);

	std::cout << std::endl << "Updated patient!" << std::endl << std::endl;
}

void Console::handleShow() {
	int option;

	std::cout << "1. Show all patients" << std::endl;
	std::cout << "2. Show a patient" << std::endl;

	std::cout << "Enter option: "; std::cin >> option;
	std::cout << std::endl;

	if (option == 1) {
		Patient** patients = this->serv.getAll();

		for (int i = 0; i < this->serv.getSize(); i++)
			patients[i]->print();
	}
	else if (option == 2) {
		std::string CNP;

		std::cin.ignore();

		std::cout << "Enter patient's CNP: "; std::getline(std::cin, CNP);

		Patient* p = this->serv.readPatient(CNP);

		if (p == nullptr) {
			std::cout << std::endl << "Invalid CNP!" << std::endl << std::endl;
			return;
		}

		p->print();
	}
	else {
		std::cout << std::endl << "Invalid option!" << std::endl << std::endl;
	}
}

void Console::handleSurgeries() {
	int option;

	std::cout << "1. Add surgery for patient" << std::endl;
	std::cout << "2. Remove surgery for patient" << std::endl;

	std::cout << "Enter option: "; std::cin >> option;
	std::cout << std::endl;

	if (option == 1) {
		std::string CNP, surgery, date;

		std::cin.ignore();

		std::cout << "Enter patient's CNP: "; std::getline(std::cin, CNP);
		std::cout << "Enter surgery's type: "; std::getline(std::cin, surgery);
		std::cout << "Enter surgery's date: "; std::getline(std::cin, date);

		bool result = this->serv.addNewSurgery(CNP, surgery, date);

		if (result) {
			std::cout << std::endl << "Added surgery successfully!" << std::endl << std::endl;
		}
		else {
			std::cout << std::endl << "Invalid CNP!" << std::endl << std::endl;
		}
	}
	else if (option == 2) {
		std::string CNP, date;

		std::cin.ignore();

		std::cout << "Enter patient's CNP: "; std::getline(std::cin, CNP);
		std::cout << "Enter surgery's date: "; std::getline(std::cin, date);

		bool result = this->serv.removeSurgery(CNP, date);

		if (result) {
			std::cout << std::endl << "Removed surgery successfully!" << std::endl << std::endl;
		}
		else {
			std::cout << std::endl << "Invalid CNP!" << std::endl << std::endl;
		}

	}
	else {
		std::cout << std::endl << "Invalid option!" << std::endl << std::endl;
	}
}

void Console::handleConsults() {
	int option;

	std::cout << "1. Add consult for patient" << std::endl;
	std::cout << "2. Remove consult for patient" << std::endl;

	std::cout << "Enter option: "; std::cin >> option;
	std::cout << std::endl;

	if (option == 1) {
		std::string CNP, consult, date;

		std::cin.ignore();

		std::cout << "Enter patient's CNP: "; std::getline(std::cin, CNP);
		std::cout << "Enter consult's type: "; std::getline(std::cin, consult);
		std::cout << "Enter consult's date: "; std::getline(std::cin, date);

		bool result = this->serv.addNewConsult(CNP, consult, date);

		if (result) {
			std::cout << std::endl << "Added consult successfully!" << std::endl << std::endl;
		}
		else {
			std::cout << std::endl << "Invalid CNP!" << std::endl << std::endl;
		}
	}
	else if (option == 2) {
		std::string CNP, date;

		std::cin.ignore();

		std::cout << "Enter patient's CNP: "; std::getline(std::cin, CNP);
		std::cout << "Enter consult's date: "; std::getline(std::cin, date);

		bool result = this->serv.removeConsult(CNP, date);

		if (result) {
			std::cout << std::endl << "Removed consult successfully!" << std::endl << std::endl;
		}
		else {
			std::cout << std::endl << "Invalid CNP!" << std::endl << std::endl;
		}
	}
	else {
		std::cout << std::endl << "Invalid option!" << std::endl << std::endl;
	}
}

void Console::handleShowSurgeries() {
	int option;

	std::cout << "1. Show surgery by date for a patient" << std::endl;
	std::cout << "2. Show all surgeries for a patient" << std::endl;

	std::cout << "Enter option: "; std::cin >> option;
	std::cout << std::endl;

	std::cin.ignore();

	switch (option) {
		case 1: {
			std::string CNP, date;

			std::cout << "Enter patient's CNP: "; std::getline(std::cin, CNP);
			std::cout << "Enter surgery date: "; std::getline(std::cin, date);
			std::cout << std::endl;

			Pair* surgery = this->serv.getSurgeryByDateForPatient(CNP, date);
			
			if (surgery != nullptr)
				std::cout << "Type: " << surgery->first << "; Date: " << surgery->second << std::endl;
			else
				std::cout << std::endl << "No surgery/patient found!" << std::endl;

			std::cout << std::endl;

			break;
		}
		case 2: {
			std::string CNP;
			std::cout << "Enter patient's CNP: "; std::getline(std::cin, CNP);
			std::cout << std::endl;

			Patient* p = this->serv.readPatient(CNP);

			if (p == nullptr) {
				std::cout << std::endl << "Patient not found!" << std::endl << std::endl;
				break;
			}

			p->printSurgeries();
			break;
		}
		default:
			std::cout << std::endl << "Invalid option!" << std::endl << std::endl;
			break;
	}
}

void Console::handleShowConsults() {
	int option;

	std::cout << "1. Show consult by date for a patient" << std::endl;
	std::cout << "2. Show all consults for a patient" << std::endl;

	std::cout << "Enter option: "; std::cin >> option;
	std::cout << std::endl;

	std::cin.ignore();

	switch (option) {
		case 1: {
			std::string CNP, date;

			std::cout << "Enter patient's CNP: "; std::getline(std::cin, CNP);
			std::cout << "Enter consult date: "; std::getline(std::cin, date);
			std::cout << std::endl;

			Pair* consult = this->serv.getConsultByDateForPatient(CNP, date);

			if (consult != nullptr)
				std::cout << "Type: " << consult->first << "; Date: " << consult->second << std::endl;
			else
				std::cout << std::endl << "No consult/patient found!" << std::endl;

			std::cout << std::endl;

			break;
		}
		case 2: {
			std::string CNP;
			std::cout << "Enter patient's CNP: "; std::getline(std::cin, CNP);
			std::cout << std::endl;

			Patient* p = this->serv.readPatient(CNP);

			if (p == nullptr) {
				std::cout << std::endl << "Patient not found!" << std::endl << std::endl;
				break;
			}

			p->printConsults();
			break;
		}
		default:
			std::cout << std::endl << "Invalid option!" << std::endl << std::endl;
			break;
	}
}

void Console::printMenu() {
	std::cout << std::endl << "1. Add patient" << std::endl;
	std::cout << "2. Discharge menu" << std::endl;
	std::cout << "3. Update patient" << std::endl;
	std::cout << "4. List patients menu" << std::endl;
	std::cout << "5. Surgeries menu" << std::endl;
	std::cout << "6. Consults menu" << std::endl;
	std::cout << "7. List surgeries menu" << std::endl;
	std::cout << "8. List consults menu" << std::endl;
	std::cout << "9. Exit" << std::endl;
}

void Console::run() {
	int option;
	std::cout << "Welcome to the hospital management system v1" << std::endl;
	this->printMenu();

	std::cout << std::endl << "Enter option: "; std::cin >> option;

	while (true) {
		switch (option) {
			case 1:
				this->handleAdd();
				break;
			case 2:
				this->handleDischarge();
				break;
			case 3:
				this->handleUpdate();
				break;
			case 4:
				this->handleShow();
				break;
			case 5:
				this->handleSurgeries();
				break;
			case 6:
				this->handleConsults();
				break;
			case 7:
				this->handleShowSurgeries();
				break;
			case 8:
				this->handleShowConsults();
				break;
			case 9:
				std::cout << std::endl << "Goodbye!";
				return;
			default:
				std::cout << std::endl << "Invalid option!" << std::endl << std::endl;
				break;
		}
		this->printMenu();

		std::cout << std::endl << "Enter option: "; std::cin >> option;
	}
}