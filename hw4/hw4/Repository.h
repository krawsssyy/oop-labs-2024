#pragma once
#include "Patient.h" // include our patient definition, via this we can access all functions, and the compiler will know to look for the definitions in the required file
// if the header is "Patient.h", then the definitions will be in "Patient.cpp"
// also, imports are transitive, since we added <string.h> and <vector> in our "Patient.h", we don't them here

class Repository {

	// this is a class that will be our "database" for patients (or whatever data types we want, since we made it for general use via templates)
	private:
		Patient** elements; // we will save pointers to our patients
		int size;
		int capacity;
	public:
		Repository();
		~Repository();

		void addElement(Patient* elem);
		void updateElement(std::string CNP, Patient* elem);
		void deleteElement(std::string CNP);
		Patient* readElement(std::string CNP);
		size_t getSize();
		Patient** getAll();
		void resize(int newSize);
};