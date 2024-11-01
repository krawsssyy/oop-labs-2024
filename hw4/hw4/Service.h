#pragma once
#include "Repository.h"

class Service {
	// this class is supposed to handle all the logic our program can perform
	// it will receive data from the user from the console, do some actions and send them further to the repo
	private:
		Repository& repo; // we want it as reference since we want to operate on the actual repository that we'll create
	public:
		Service(Repository& repo);
		~Service() {}; // destructor is empty
		void addPatient(std::string name, std::string CNP, int age, std::string diagnosis, Pair* surgeries, int sizeSurgeries, Pair* consults, int sizeConsults);
		bool updatePatient(std::string origCNP, std::string name, std::string CNP, int age, std::string diagnosis, Pair* surgeries, int sizeSurgeries, Pair* consults, int sizeConsults);
		bool deletePatient(std::string CNP);
		Patient* readPatient(std::string CNP);
		Patient** getAll();
		size_t getSize();

		bool addNewConsult(std::string CNP, std::string consult, std::string date);
		bool removeConsult(std::string CNP, std::string date);

		bool addNewSurgery(std::string CNP, std::string surgery, std::string date);
		bool removeSurgery(std::string CNP, std::string date);

		bool markAsHealed(std::string CNP);

		Pair* getConsultByDateForPatient(std::string CNP, std::string date);
		Pair* getSurgeryByDateForPatient(std::string CNP, std::string date);
};