#pragma once
#include <fstream>
#include "Stack.h" // we include stack since it contains Book.h, so we only include one file and avoid reinclusions
// we'll include repo in our service, and with this we'll also have access to the stack we created
class Repository {
	private:
		Book** elements;
		size_t size;
		size_t capacity;
	public:
		Repository();
		~Repository();

		void addElement(Book* elem);
		void updateElement(std::string ISBN, Book* elem);
		void deleteElement(std::string ISBN);
		Book* readElement(std::string ISBN);
		size_t getSize();
		Book** getAll();
		void setVector(Book** vector, size_t size);
		void resize(int newSize);
};