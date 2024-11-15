#pragma once
#include <iostream>

class Cage {
	private:
		inline static int counter = 0;
		int id;
		int supervisorID;
		int animalIDs[10]; // assign a default size for each cage, since it wouldn't make sense for it to have resizable capacity
	public:
		Cage() = default;
		Cage(int supervisorID, int* animalIDs) : id(counter++), supervisorID(supervisorID) {
			for (int i = 0; i < 10; i++)
				this->animalIDs[i] = animalIDs[i];
		}
		~Cage() {}
		int getID() { return this->id; }
		void setSupervisorID(int supervisorID) { this->supervisorID = supervisorID; }
		int getSupervisorID() { return this->supervisorID; }
		int* getAnimalIDs() { return this->animalIDs; }
		bool addAnimal(int ID) {
			int idx = -1;
			for(int i = 0; i < 10; i++) // ensure we have space to add
				if (this->animalIDs[i] == -1) {
					idx = i;
					break;
				}
			if (idx != -1) {
				this->animalIDs[idx] = ID;
				return true;
			}
			return false;
		}

		bool removeAnimal(int ID) {
			for (int i = 0; i < 10; i++)
				if (this->animalIDs[i] == ID) {
					this->animalIDs[i] = -1;
					return true;
				}
			return false;
		}

		void print() {
			std::cout << std::endl << "Cage" << std::endl << "ID: " << this->id << std::endl
				<< "Supervisor ID: " << this->supervisorID << std::endl << "Animal IDs: " << std::endl;
			for (int i = 0; i < 10; i++)
				if (this->animalIDs[i] != -1)
					std::cout << this->animalIDs[i] << " ";
			std::cout << std::endl << std::endl;
		}
};
