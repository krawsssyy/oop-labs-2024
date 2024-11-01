#pragma once // tells the compiler to only parse this file once, thus allowing us to include files that include this
#include "Pair.h"
#include <iostream>
// header file, it is used only for definitions
class Patient {
	private: // ideally, due to encapsulation, we'd want to make all our attributes private and only refer to them via getters/setters
		std::string name;
		std::string CNP;
		int age;
		std::string diagnosis;
		bool healed;
		Pair* surgeries;
		int sizeSurgeries;
		Pair* consults;
		int sizeConsults;
	public:
		Patient();
		Patient(std::string name, std::string CNP, int age, std::string diagnosis, Pair* surgeries, int sizeSurgeries, Pair* consults, int sizeConsults);
		Patient(const Patient& patient);
		~Patient();
		void setName(std::string name);
		std::string getName();
		void setCNP(std::string CNP);
		std::string getCNP();
		void setAge(int age);
		int getAge();
		void setDiagnosis(std::string diagnosis);
		std::string getDiagnosis();
		void setHeal(bool healed);
		bool getHeal();
		void setSurgeries(Pair* surgeries, int sizeSurgeries);
		Pair* getSurgeries();
		int getSurgeriesSize();
		void setConsults(Pair* consults, int sizeConsults);
		Pair* getConsults();
		int getConsultsSize();
		void print();
		void printSurgeries();
		void printConsults();
};