#pragma once
#include "RepositoryAnimal.h"
#include "RepositoryCage.h"
#include "RepositorySupervisor.h"

class Service {
	private:
		RepositoryAnimal& repoAnimal;
		RepositoryCage& repoCage;
		RepositorySupervisor& repoSupervisor;
	public:
		Service(RepositoryAnimal& repoAnimal, RepositoryCage& repoCage, RepositorySupervisor& repoSupervisor) : repoAnimal(repoAnimal), repoCage(repoCage), repoSupervisor(repoSupervisor) {}
		~Service() {}

		bool addAnimal(int cageID, std::string name, std::string race, float height, float weight);
		bool updateAnimal(int ID, int cageID, std::string name, std::string race, float height, float weight);
		bool deleteAnimal(int ID);
		Animal* readAnimal(int ID);
		Animal** getAllAnimals();
		int getAnimalsSize();

		bool addCage(int supervisorID, int* animalIDs);
		bool updateCage(int ID, int supervisorID, int* animalIDs);
		bool deleteCage(int ID);
		Cage* readCage(int ID);
		Cage** getAllCages();
		int getCagesSize();

		bool addSupervisor(std::string name, int cageID);
		bool updateSupervisor(int ID, std::string name, int cageID);
		bool deleteSupervisor(int ID);
		Supervisor* readSupervisor(int ID);
		Supervisor** getAllSupervisors();
		int getSupervisorsSize();

		bool assignAnimalToCage(int animalID, int cageID);
		bool removeAnimalFromCage(int animalID, int cageID);

		bool assignSupervisorToCage(int supervisorID, int cageID);
		bool removeSupervisorFromCage(int supervisorID, int cageID);
};