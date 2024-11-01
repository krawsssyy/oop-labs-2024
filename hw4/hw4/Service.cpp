#include "Service.h"

Service::Service(Repository& repo) : repo(repo) {}

void Service::addPatient(std::string name, std::string CNP, int age, std::string diagnosis, Pair* surgeries, int sizeSurgeries, Pair* consults, int sizeConsults) {
	Patient* p = new Patient(name, CNP, age, diagnosis, surgeries, sizeSurgeries, consults, sizeConsults);
	this->repo.addElement(p);
}

bool Service::updatePatient(std::string origCNP, std::string name, std::string CNP, int age, std::string diagnosis, Pair* surgeries, int sizeSurgeries, Pair* consults, int sizeConsults) {
	Patient* orig = this->repo.readElement(origCNP);

	if (orig == nullptr)
		return false;

	Patient* p = new Patient(name, CNP, age, diagnosis, surgeries, sizeSurgeries, consults, sizeConsults);
	this->repo.updateElement(origCNP, p);

	return true;
}

bool Service::deletePatient(std::string CNP) {
	Patient* orig = this->repo.readElement(CNP);

	if (orig == nullptr)
		return false;

	this->repo.deleteElement(CNP);
	
	return true;
}

Patient* Service::readPatient(std::string CNP) {
	return this->repo.readElement(CNP);
}

Patient** Service::getAll() {
	return this->repo.getAll();
}

size_t Service::getSize() {
	return this->repo.getSize();
}

bool Service::addNewConsult(std::string CNP, std::string consult, std::string date) {
	Patient* p = this->repo.readElement(CNP);

	if (p == nullptr)
		return false;

	int size = p->getConsultsSize();
	Pair* consults = p->getConsults();
	Pair* newConsults = new Pair[size + 1];
	Pair newConsult(consult, date);

	memcpy(newConsults, consults, sizeof(Pair) * size);
	newConsults[size] = newConsult;

	p->setConsults(newConsults, size + 1);

	delete[] consults; // cleanup for the dynamic memory allocated in getConsults
	consults = nullptr;

	return true;
}

bool Service::removeConsult(std::string CNP, std::string date) {
	Patient *p = this->repo.readElement(CNP);

	if (p == nullptr)
		return false;

	Pair* consults = p->getConsults();
	int size = p->getConsultsSize();
	int idx = -1;
	for (int i = 0; i < size; i++)
		if (consults[i].second == date) {
			idx = i;
			break;
		}

	if (idx == -1) { // if we didn't find that consult
		delete[] consults;
		consults = nullptr;
		return false;
	}

	if (idx == size - 1) {
		Pair* newConsults = new Pair[size - 1];
		for (int i = 0; i < size - 1; i++)
			newConsults[i] = consults[i];
		p->setConsults(newConsults, size - 1);
	}
	else {
		Pair* newConsults = new Pair[size - 1];
		for (int i = 0; i < idx; i++)
			newConsults[i] = consults[i];
		for (int i = idx; i < size - 1; i++)
			newConsults[i] = consults[i + 1];
		p->setConsults(newConsults, size - 1);
	}
	
	delete[] consults;
	consults = nullptr;
	return true;

	return true;
}

bool Service::addNewSurgery(std::string CNP, std::string surgery, std::string date) {
	Patient* p = this->repo.readElement(CNP);

	if (p == nullptr)
		return false;

	int size = p->getSurgeriesSize();
	Pair* surgeries = p->getSurgeries();
	Pair* newSurgeries = new Pair[size + 1];
	Pair newSurgery(surgery, date);

	memcpy(newSurgeries, surgeries, sizeof(Pair) * size);
	newSurgeries[size] = newSurgery;

	p->setSurgeries(newSurgeries, size + 1);

	delete[] surgeries; // cleanup for the dynamic memory allocated in getSurgeries
	surgeries = nullptr;

	return true;
}

bool Service::removeSurgery(std::string CNP, std::string date) {
	Patient* p = this->repo.readElement(CNP);

	if (p == nullptr)
		return false;

	Pair* surgeries = p->getSurgeries();
	int size = p->getSurgeriesSize();
	int idx = -1;
	for (int i = 0; i < size; i++)
		if (surgeries[i].second == date) {
			idx = i;
			break;
		}

	if (idx == -1) { // if we didn't find that consult
		delete[] surgeries;
		surgeries = nullptr;
		return false;
	}

	if (idx == size - 1) {
		Pair* newSurgeries = new Pair[size - 1];
		for (int i = 0; i < size - 1; i++)
			newSurgeries[i] = surgeries[i];
		p->setSurgeries(newSurgeries, size - 1);
	}
	else {
		Pair* newSurgeries = new Pair[size - 1];
		for (int i = 0; i < idx; i++)
			newSurgeries[i] = surgeries[i];
		for (int i = idx; i < size - 1; i++)
			newSurgeries[i] = surgeries[i + 1];
		p->setSurgeries(newSurgeries, size - 1);
	}

	delete[] surgeries;
	surgeries = nullptr;
	return true;

	return true;
}

bool Service::markAsHealed(std::string CNP) {
	Patient* p = this->repo.readElement(CNP);

	if (p == nullptr)
		return false;

	p->setHeal(true);

	this->deletePatient(CNP);

	return true;
}


Pair* Service::getConsultByDateForPatient(std::string CNP, std::string date) {
	Patient* p = this->repo.readElement(CNP);

	if (p == nullptr)
		return nullptr;

	Pair* consults = p->getConsults();
	Pair* retVal = nullptr;

	for (int i = 0; i < p->getConsultsSize(); i++)
		if (consults[i].second == date) {
			retVal = &consults[i];
			break;
		}

	delete[] consults;
	consults = nullptr;
	return retVal;
	// ideally we'd want to differentiate whether we didn't find the patient, or it just has no consults, but that'll come later with custom exceptions
}

Pair* Service::getSurgeryByDateForPatient(std::string CNP, std::string date) {
	Patient* p = this->repo.readElement(CNP);

	if (p == nullptr)
		return nullptr;

	Pair* surgeries = p->getSurgeries();
	Pair* retVal = nullptr;

	for (int i = 0; i < p->getSurgeriesSize(); i++)
		if (surgeries[i].second == date) {
			retVal = &surgeries[i];
			break;
		}

	delete[] surgeries;
	surgeries = nullptr;
	return retVal;
}
