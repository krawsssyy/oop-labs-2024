#include "Service.h"

bool Service::addAnimal(int cageID, std::string name, std::string race, float height, float weight) {
	if (this->repoCage.readElement(cageID) == nullptr)
		return false;

	this->repoAnimal.addElement(new Animal(cageID, name, race, height, weight)); // we can also define variables inside function calls, as such
	return true;
}

bool Service::updateAnimal(int ID, int cageID, std::string name, std::string race, float height, float weight) {
	if (this->repoAnimal.readElement(ID) == nullptr)
		return false;

	if (this->repoCage.readElement(cageID) == nullptr)
		return false;

	this->repoAnimal.updateElement(ID, new Animal(cageID, name, race, height, weight));
	return true;
}

bool Service::deleteAnimal(int ID) {
	if (this->repoAnimal.readElement(ID) == nullptr)
		return false;

	this->repoAnimal.deleteElement(ID);
	return true;
}

Animal* Service::readAnimal(int ID) {
	return this->repoAnimal.readElement(ID);
}

Animal** Service::getAllAnimals() {
	return this->repoAnimal.getAll();
}

int Service::getAnimalsSize() {
	return this->repoAnimal.getSize();
}

bool Service::addCage(int supervisorID, int* animalIDs) {
	for (int i = 0; i < 10; i++)
		if (this->repoAnimal.readElement(animalIDs[i]) == nullptr && animalIDs[i] != -1)
			return false;

	this->repoCage.addElement(new Cage(supervisorID, animalIDs));
	return true;
}

bool Service::updateCage(int ID, int supervisorID, int* animalIDs) {
	if (this->repoCage.readElement(ID) == nullptr)
		return false;

	this->repoCage.updateElement(ID, new Cage(supervisorID, animalIDs));
	return true;
}

bool Service::deleteCage(int ID) {
	if (this->repoCage.readElement(ID) == nullptr)
		return false;

	this->repoCage.deleteElement(ID);
	return true;
}

Cage* Service::readCage(int ID) {
	return this->repoCage.readElement(ID);
}

Cage** Service::getAllCages() {
	return this->repoCage.getAll();
}

int Service::getCagesSize() {
	return this->repoCage.getSize();
}

bool Service::addSupervisor(std::string name, int cageID) {
	if (this->repoCage.readElement(cageID) == nullptr)
		return false;

	this->repoSupervisor.addElement(new Supervisor(name, cageID));
	return true;
}

bool Service::updateSupervisor(int ID, std::string name, int cageID) {
	if (this->repoSupervisor.readElement(ID) == nullptr)
		return false;

	this->repoSupervisor.updateElement(ID, new Supervisor(name, cageID));
	return true;
}

bool Service::deleteSupervisor(int ID) {
	if (this->repoCage.readElement(ID) == nullptr)
		return false;

	this->repoSupervisor.deleteElement(ID);
	return true;
}

Supervisor* Service::readSupervisor(int ID) {
	return this->repoSupervisor.readElement(ID);
}

Supervisor** Service::getAllSupervisors() {
	return this->repoSupervisor.getAll();
}

int Service::getSupervisorsSize() {
	return this->repoSupervisor.getSize();
}

bool Service::assignAnimalToCage(int animalID, int cageID) {
	Animal* elem = this->repoAnimal.readElement(animalID);

	if (elem == nullptr)
		return false;

	Cage* elemCage = this->repoCage.readElement(cageID);

	if (elemCage == nullptr)
		return false;

	bool res = elemCage->addAnimal(animalID);

	if (res) {
		this->repoCage.updateElement(cageID, elemCage);
		return true;
	}
	else
		return false;
}

bool Service::removeAnimalFromCage(int animalID, int cageID) {
	if (this->repoAnimal.readElement(animalID) == nullptr)
		return false;

	Cage* elemCage = this->repoCage.readElement(cageID);

	if (elemCage == nullptr)
		return false;

	bool res = elemCage->removeAnimal(animalID);

	if (res) {
		this->repoCage.updateElement(cageID, elemCage);
		return true;
	}
	else
		return false;
}

bool Service::assignSupervisorToCage(int supervisorID, int cageID) {
	Supervisor* elem = this->repoSupervisor.readElement(supervisorID);

	if (elem == nullptr)
		return false;

	Cage* elemCage = this->repoCage.readElement(cageID);

	if (elemCage == nullptr)
		return false;

	elem->setCageID(cageID);
	elemCage->setSupervisorID(supervisorID);

	this->repoSupervisor.updateElement(supervisorID, elem);
	this->repoCage.updateElement(cageID, elemCage);

	return true;
}

bool Service::removeSupervisorFromCage(int supervisorID, int cageID) {
	Supervisor* elem = this->repoSupervisor.readElement(supervisorID);

	if (elem == nullptr)
		return false;

	Cage* elemCage = this->repoCage.readElement(cageID);

	if (elemCage == nullptr)
		return false;

	elem->setCageID(-1);
	elemCage->setSupervisorID(-1);

	this->repoSupervisor.updateElement(supervisorID, elem);
	this->repoCage.updateElement(cageID, elemCage);

	return true;
}