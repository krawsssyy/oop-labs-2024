#pragma once
#include "Repository.h"

class Service {
	private:
		Repository& r;
		Stack* s;
	public:
		Service(Repository& r) : r(r) { this->s = new Stack(); }
		~Service() {
			// we use stack as a pointer to control its lifetime, and ensure that it gets deleted first, so as not to have dangling pointers or double frees somewhere
			delete this->s;
			this->s = nullptr;
		}

		void addBook(std::string title, std::string author, std::string ISBN, std::string publisher, int year, bool borrowed);
		bool updateBook(std::string origISBN, std::string title, std::string author, std::string ISBN, std::string publisher, int year, bool borrowed);
		Book* readBook(std::string ISBN);
		bool deleteBook(std::string ISBN);
		Book** getAll();
		size_t getSize();

		bool isBorrowed(std::string ISBN);
		bool borrow(std::string ISBN);

		bool undo();
};