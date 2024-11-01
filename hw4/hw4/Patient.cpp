#include "Patient.h" // include our defined header file

Patient::Patient() { // define the non-parametrized constructor
	// for defining the functions outside the class definition, we have this format
	// CLASSNAME::FUNCTIONNAME
	// similar to how namespaces work, and that's why when we don't do "using namespace std", you have to use "std::cout" or "std::string" and so on
	// using that, it tells the compiler that this is part of the class declaration, and as such we can use the "this" pointer
	// we also need to keep the same function name and same parameters, even with their names, so it has to reflect perfectly how we defined the function in the header file
	this->name = this->CNP = this->diagnosis = "";
	this->age = 0;
	this->healed = false;
	this->surgeries = new Pair[10]; // allocate some initial size
	this->consults = new Pair[10];
}

Patient::Patient(std::string name, std::string CNP, int age, std::string diagnosis, Pair* surgeries, int sizeSurgeries, Pair* consults, int sizeConsults) : name(name), CNP(CNP), age(age), diagnosis(diagnosis), sizeSurgeries(sizeSurgeries), sizeConsults(sizeConsults) {
	// faster way to define a simple constructor
	// after the ":", we have memberVariable(parameterToInitializeItWith)
	// the values are separated by commas
	// what is left is to initialize the vectors
	this->surgeries = new Pair[this->sizeSurgeries];
	this->consults = new Pair[this->sizeConsults];
    // we use memcpy to copy memory, so as to not get the actual pointers into our list
	memcpy(this->surgeries, surgeries, sizeof(Pair) * this->sizeSurgeries);
	memcpy(this->consults, consults, sizeof(Pair) * this->sizeConsults);
} 

Patient::Patient(const Patient& patient) { // define the copy constructor
	this->name = patient.name;
	this->CNP = patient.CNP;
	this->age = patient.age;
	this->diagnosis = patient.diagnosis;
	this->healed = patient.healed;
	this->sizeSurgeries = patient.sizeSurgeries;
	this->sizeConsults = patient.sizeConsults;

	this->surgeries = new Pair[this->sizeSurgeries];
	this->consults = new Pair[this->sizeConsults];

	memcpy(this->surgeries, patient.surgeries, sizeof(Pair) * this->sizeSurgeries);
	memcpy(this->consults, patient.consults, sizeof(Pair) * this->sizeConsults);
}

Patient::~Patient() { // cleanup
	delete[] this->surgeries;
	delete[] this->consults;

	this->surgeries = nullptr;
	this->consults = nullptr;
}

void Patient::setName(std::string name) {
	this->name = name;
}

std::string Patient::getName() {
	return this->name;
}

void Patient::setCNP(std::string CNP) {
	this->CNP = CNP;
}

std::string Patient::getCNP() {
	return this->CNP;
}

void Patient::setAge(int age) {
	this->age = age;
}

int Patient::getAge() {
	return this->age;
}

void Patient::setDiagnosis(std::string diagnosis) {
	this->diagnosis = diagnosis;
}

std::string Patient::getDiagnosis() {
	return this->diagnosis;
}

void Patient::setHeal(bool healed) {
	this->healed = healed;
}

bool Patient::getHeal() {
	return this->healed;
}


void Patient::setSurgeries(Pair* surgeries, int sizeSurgeries) {
	this->sizeSurgeries = sizeSurgeries;

	// delete old vector
	delete[] this->surgeries;
	// allocate new memory
	this->surgeries = new Pair[this->sizeSurgeries];
	memcpy(this->surgeries, surgeries, sizeof(Pair) * this->sizeSurgeries);
}

Pair* Patient::getSurgeries() {
	Pair* cpy = new Pair[this->sizeSurgeries]; // create a copy so we don't send our actual values
	memcpy(cpy, this->surgeries, sizeof(Pair) * this->sizeSurgeries);
	return cpy;
}

int Patient::getSurgeriesSize() {
	return this->sizeSurgeries;
}


void Patient::setConsults(Pair* consults, int sizeConsults) {
	this->sizeConsults = sizeConsults;

	// delete old vector
	delete[] this->consults;
	// allocate new memory
	this->consults = new Pair[this->sizeConsults];
	memcpy(this->consults, consults, sizeof(Pair) * this->sizeConsults);
}

Pair* Patient::getConsults() {
	Pair* cpy = new Pair[this->sizeConsults];
	memcpy(cpy, this->consults, sizeof(Pair) * this->sizeConsults);
	return cpy;
}

int Patient::getConsultsSize() {
	return this->sizeConsults;
}

void Patient::print() {
	// pretty print the patients info

	std::cout << "Name: " << this->name << std::endl;
	std::cout << "CNP: " << this->CNP << std::endl;
	std::cout << "Age: " << this->age << std::endl;
	std::cout << "Diagnosis: " << this->diagnosis << std::endl;
	std::cout << "Is healed: " << (this->healed ? "true" : "false") << std::endl;

	std::cout << "Surgeries: " << std::endl;
	for (int i = 0; i < this->sizeSurgeries; i++)
		std::cout << "Type: " << this->surgeries[i].first << "; Date: " << this->surgeries[i].second << std::endl; // accessing the first element of a pair is done via .first, and the second is via .second

	std::cout << "Consults: " << std::endl;
	for (int i = 0; i < this->sizeConsults; i++)
		std::cout << "Type: " << this->consults[i].first << "; Date: " << this->consults[i].second << std::endl;

	std::cout << std::endl;
}

void Patient::printSurgeries() {
	std::cout << "Surgeries for patient: " << this->CNP << std::endl;
	for (int i = 0; i < this->sizeSurgeries; i++)
		std::cout << "Type: " << this->surgeries[i].first << "; Date: " << this->surgeries[i].second << std::endl;

	std::cout << std::endl;
}

void Patient::printConsults() {
	std::cout << "Consults for patient: " << this->CNP << std::endl;
	for (int i = 0; i < this->sizeConsults; i++)
		std::cout << "Type: " << this->consults[i].first << "; Date: " << this->consults[i].second << std::endl;

	std::cout << std::endl;
}