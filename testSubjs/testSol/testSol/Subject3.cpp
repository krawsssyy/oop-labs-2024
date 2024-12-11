#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <iostream>

enum Genre {FICTION, NONFICTION, SCIENCE};

class LibraryBook {
	private:
		enum Genre genre;
		char* title;
		int pages;
		const std::string author;
		static int totalBooks;
		static int magicLen;
	public:
		LibraryBook() : genre(FICTION), pages(0), author("") { // default constructor
			this->title = new char[strlen("default") + 1];
			strcpy(this->title, "default");
			totalBooks++;
		}
		void setTitle(const char* title) { // setter
			if (strlen(title) < magicLen) // check for length
				throw std::exception("Title doesn't have the required length!");
			delete[] this->title; // delete old memory for the title
			this->title = new char[strlen(title) + 1];
			strcpy(this->title, title); // copy new title
		}

		char* getTitle() { // getter
			char* cpy = new char[strlen(this->title)];
			strcpy(cpy, this->title); // create copy an return it
			return cpy;
		}

		LibraryBook(enum Genre genre, const char* title, int pages, std::string author) : genre(genre), author(author) { // parametrized constructor
			if (pages > 0) // ensure good pages
				this->pages = pages;
			else
				this->pages = 0;

			if (strlen(title) >= magicLen) { // ensure good title
				this->title = new char[strlen(title) + 1];
				strcpy(this->title, title);
			}
			else {
				this->title = new char[strlen("default") + 1];
				strcpy(this->title, "default");
			}

			totalBooks++;
		}

		~LibraryBook() { // destructor
			delete[] this->title;
			this->title = nullptr;
		}

		LibraryBook(const LibraryBook& lb): genre(lb.genre), pages(lb.pages), author(lb.author) { // copy constructor
			this->title = new char[strlen(lb.title) + 1];
			strcpy(this->title, lb.title);

			totalBooks++;
		}

		static int getTotal() { return totalBooks; } // static getter for the static variable totalBooks

		LibraryBook& operator=(const LibraryBook& lb) { // operator= overload
			if (this != &lb) { // avoid self-reference
				this->~LibraryBook(); // explicitly call destructor
				new (this) LibraryBook(lb); // recreate the current class in place from the given book
				// this is done to correctly reassign the const attribute
				// else, just don't copy the const attribute, since after initialization it cannot be modified
			}
			return *this;
		}

		friend std::ostream& operator<<(std::ostream& os, const LibraryBook& lb); // define it as friend since it will need access to private attributes
		friend void operator++(LibraryBook& lb, int var); // define it as friend, and declare it outside to be the postfixed version

		bool operator>=(const LibraryBook& lb) {
			if (this->pages < lb.pages)
				return false;

			if (strlen(this->title) < strlen(lb.title))
				return false;

			if (strcmp(this->title, lb.title) < 0)
				return false;

			return true;

		}

		bool checkTitle(const char* title) { return strcmp(this->title, title) == 0; }

		double getReadingTime() { return (double)this->pages / 50.f; }
};

int LibraryBook::totalBooks = 0;
int LibraryBook::magicLen = 4;

std::ostream& operator<<(std::ostream& os, const LibraryBook& lb) { // define operator<<
	std::string genre;
	if (lb.genre == FICTION)
		genre = "FICTION";
	else if (lb.genre == NONFICTION)
		genre = "NONFICTION";
	else
		genre = "SCIENCE";
	os << "Genre: " << genre << "; Title: " << lb.title << "; Pages: " << lb.pages << "; Author: " << lb.author << '\n';
	return os;
}

void operator++(LibraryBook& lb, int var) {
	lb.pages += 10;
}

//int main() {
//	LibraryBook b1(); // test default constructor
//	LibraryBook b2(FICTION, "Harry Potter", 304, "J.K. Rowling"); // test parametrized constructor
//	
//	b2.setTitle("War and Peace"); // test title setter
//	char* resTitle = b2.getTitle();
//	std::cout << resTitle << std::endl; // test title getter
//	delete[] resTitle;
//	resTitle = nullptr; // cleanup returned pointer
//
//	LibraryBook* b3 = new LibraryBook(); // create pointer to test destructor
//	delete b3; // test destructor
//	b3 = nullptr;
//
//	LibraryBook b4(b2); // test copy constructor
//
//	LibraryBook b5 = b2; // test operator=
//
//	std::cout << b5; // test operator<<
//
//	b5++; // test operator++
//
//	if (b5 >= b2) // test operator>=
//		std::cout << "b5 >= b2" << std::endl;
//	else
//		std::cout << "b5 < b2" << std::endl;
//
//	bool res = b5.checkTitle("Harry Potter"); // test the title checking function
//
//	std::cout << "Reading time: " << b5.getReadingTime() << std::endl; // test reading time function
//
//	return 0;
//}