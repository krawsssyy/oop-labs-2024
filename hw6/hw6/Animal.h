#pragma once
#include <string>
#include <iostream>

class Animal {
	private:
		inline static int counter = 0; // static variable to be used as a counter for the ID
		// will be initialized with 0, and each new entity will increment it
		int id;
		int cageID;
		std::string name;
		std::string race;
		float height;
		float weight;
		void setID(int id) { this->id = id; } // made private so the ID cannot be changed externally, only internally by the class
		// in our case it won't be used, but I left it here for future reference, so you be aware to make setting identifiable attributes a private operation
	public:
		Animal() = default;
		Animal(int cageID, std::string name, std::string race, float height, float weight) : id(counter++), cageID(cageID), name(name), race(race), height(height), weight(weight) {}
		~Animal() {}
		int getID() { return this->id; } // made everything in the header file since the definitions were simple and it allows us to save space
		void setCageID(int cageID) { this->cageID = cageID; }
		int getCageID() { return this->cageID; }
		std::string getName() { return this->name; }
		void setName(std::string name) { this->name = name; }
		std::string getRace() { return this->race; }
		void setRace(std::string race) { this->race = race; }
		float getHeight() { return this->height; }
		void setHeight(float height) { this->height = height; }
		float getWeight() { return this->weight; }
		void setWeight(float weight) { this->weight = weight; }
		void print() {
			std::cout << std::endl << "Animal" << std::endl << "ID: " << this->id << std::endl
				<< "Name: " << this->name << std::endl << "Race: " << this->race << std::endl
				<< "Height: " << this->height << std::endl << "Weight: " << this->weight << std::endl << std::endl;
		}
};