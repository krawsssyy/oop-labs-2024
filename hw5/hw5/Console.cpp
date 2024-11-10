#include "Console.h"

void Console::printMenu() {
	std::cout << std::endl;
	std::cout << "1. Add book" << std::endl;
	std::cout << "2. Get book" << std::endl;
	std::cout << "3. Update book" << std::endl;
	std::cout << "4. Remove book" << std::endl;
	std::cout << "5. Borrow book" << std::endl;
	std::cout << "6. Return book" << std::endl;
	std::cout << "7. List books" << std::endl;
	std::cout << "8. Undo last operation" << std::endl;
	std::cout << "9. Exit" << std::endl << std::endl;
}

void Console::handleAdd() {
	std::string title, author, ISBN, publisher;
	char borrow;
	int year;
	bool borrowed;

	std::cin.ignore();
	std::cout << "Title: "; std::getline(std::cin, title);
	std::cout << "Author: "; std::getline(std::cin, author);
	std::cout << "ISBN: "; std::getline(std::cin, ISBN);
	std::cout << "Publisher: "; std::getline(std::cin, publisher);
	std::cout << "Year: "; std::cin >> year;
	std::cout << "Is it borrowed? (Y/N): "; std::cin >> borrow;

	if (tolower(borrow) == 'y')
		borrowed = true;
	else if (tolower(borrow) == 'n')
		borrowed = false;
	else {
		std::cout << std::endl << "Wrong option for borrow! Try again." << std::endl;
		return;
	}

	if (year < 0 || year > 2024) {
		std::cout << std::endl << "Year cannot be smaller than 0 or greater than the current year! Try again." << std::endl;
		return;
	}

	if (this->s.readBook(ISBN) != nullptr) {
		std::cout << std::endl << "Book with given ISBN already exists! Try again." << std::endl;
		return;
	}

	this->s.addBook(title, author, ISBN, publisher, year, borrowed);
	std::cout << std::endl << "Book added successfully!" << std::endl;
}

void Console::handleRead() {
	std::string ISBN;

	std::cin.ignore();
	std::cout << "Enter ISBN of book to display: "; std::getline(std::cin, ISBN);

	Book* book = this->s.readBook(ISBN);

	if (book == nullptr) {
		std::cout << std::endl << "Book doesn't exist! Try again." << std::endl;
		return;
	}

	book->print();
}

void Console::handleUpdate() {
	std::string origISBN, title, author, ISBN, publisher;
	char borrow;
	int year;
	bool borrowed;

	std::cin.ignore();
	std::cout << "Original book's ISBN: "; std::getline(std::cin, origISBN);
	std::cout << "New title: "; std::getline(std::cin, title);
	std::cout << "New author: "; std::getline(std::cin, author);
	std::cout << "New ISBN: "; std::getline(std::cin, ISBN);
	std::cout << "New publisher: "; std::getline(std::cin, publisher);
	std::cout << "New year: "; std::cin >> year;
	std::cout << "Is it borrowed? (Y/N): "; std::cin >> borrow;

	if (tolower(borrow) == 'y')
		borrowed = true;
	else if (tolower(borrow) == 'n')
		borrowed = false;
	else {
		std::cout << std::endl << "Wrong option for borrow! Try again." << std::endl;
		return;
	}

	if (year < 0 || year > 2024) {
		std::cout << std::endl << "Year cannot be smaller than 0 or greater than the current year! Try again." << std::endl;
		return;
	}

	if (this->s.readBook(ISBN) != nullptr) {
		std::cout << std::endl << "Book with the new ISBN already exists! Try again." << std::endl;
		return;
	}

	bool res = this->s.updateBook(origISBN, title, author, ISBN, publisher, year, borrowed);
	if (res)
		std::cout << std::endl << "Book added successfully!" << std::endl;
	else
		std::cout << std::endl << "Original book doesn't exist! Try again." << std::endl;
}

void Console::handleDelete() {
	std::string ISBN;

	std::cin.ignore();
	std::cout << "Enter ISBN of book to delete: "; std::getline(std::cin, ISBN);

	bool res = this->s.deleteBook(ISBN);

	if (res)
		std::cout << std::endl << "Book deleted successfully!" << std::endl;
	else
		std::cout << std::endl << "Book to delete doesn't exist! Try again." << std::endl;
}

void Console::handleBorrow() {
	std::string ISBN;

	std::cin.ignore();
	std::cout << "Enter ISBN of book to borrow: "; std::getline(std::cin, ISBN);

	if (this->s.isBorrowed(ISBN))
		std::cout << std::endl << "Book is already borrowed! Try again." << std::endl;
	else {
		this->s.borrow(ISBN);
		std::cout << std::endl << "Book borrowed successfully!" << std::endl;
	}
}

void Console::handleReturn() {
	std::string ISBN;

	std::cin.ignore();
	std::cout << "Enter ISBN of book to return: "; std::getline(std::cin, ISBN);

	if (!this->s.isBorrowed(ISBN))
		std::cout << std::endl << "Book is not borrowed! Try again." << std::endl;
	else {
		this->s.borrow(ISBN);
		std::cout << std::endl << "Book returned successfully!" << std::endl;
	}
}

void Console::handleShow() {
	int option;

	std::cout << "1. Show all books" << std::endl;
	std::cout << "2. Show all books by the given author" << std::endl;
	std::cout << "3. Show all books by the given publisher" << std::endl;
	std::cout << "4. Show all books published in the given year" << std::endl;
	std::cout << "5. List all borrowed books" << std::endl;
	std::cout << "6. List all books not borrowed" << std::endl << std::endl;

	std::cout << "Enter option: "; std::cin >> option;

	switch (option) {
		case 1: {
			Book** books = this->s.getAll();
			size_t size = this->s.getSize();

			for (int i = 0; i < size; i++)
				books[i]->print();

			delete[] books;
			books = nullptr;
			break;
		}
		case 2: {
			std::string author;

			std::cin.ignore();
			std::cout << "Enter author to filter by: "; std::getline(std::cin, author);

			Book** books = this->s.getAll();
			size_t size = this->s.getSize();

			for (int i = 0; i < size; i++)
				if (books[i]->getAuthor() == author)
					books[i]->print();

			delete[] books;
			books = nullptr;
			break;
		}
		case 3: {
			std::string publisher;

			std::cin.ignore();
			std::cout << "Enter publisher to filter by: "; std::getline(std::cin, publisher);

			Book** books = this->s.getAll();
			size_t size = this->s.getSize();

			for (int i = 0; i < size; i++)
				if (books[i]->getPublisher() == publisher)
					books[i]->print();

			delete[] books;
			books = nullptr;
			break;
		}
		case 4: {
			int year;
			std::cout << "Enter year to filter by: "; std::cin >> year;

			Book** books = this->s.getAll();
			size_t size = this->s.getSize();

			for (int i = 0; i < size; i++)
				if (books[i]->getYear() == year)
					books[i]->print();

			delete[] books;
			books = nullptr;
			break;
		}
		case 5: {
			Book** books = this->s.getAll();
			size_t size = this->s.getSize();

			for (int i = 0; i < size; i++)
				if (books[i]->getBorrow())
					books[i]->print();

			delete[] books;
			books = nullptr;
			break;
		}
		case 6: {
			Book** books = this->s.getAll();
			size_t size = this->s.getSize();

			for (int i = 0; i < size; i++)
				if (!books[i]->getBorrow())
					books[i]->print();

			delete[] books;
			books = nullptr;
			break;
		}
		default: {
			std::cout << std::endl << "Invalid option! Try again." << std::endl;
			break;
		}
	}
}

void Console::handleUndo() {
	bool res = this->s.undo();

	if (res)
		std::cout << std::endl << "Successfully undid the last operation!" << std::endl;
	else
		std::cout << std::endl << "There is no operation to undo! Try again." << std::endl;
}

void Console::run() {
	int option;

	this->printMenu();

	std::cout << "Enter option: "; std::cin >> option;
	std::cout << std::endl;

	while (true) {
		switch (option) {
			case 1:
				this->handleAdd();
				break;
			case 2:
				this->handleRead();
				break;
			case 3:
				this->handleUpdate();
				break;
			case 4:
				this->handleDelete();
				break;
			case 5:
				this->handleBorrow();
				break;
			case 6:
				this->handleReturn();
				break;
			case 7:
				this->handleShow();
				break;
			case 8:
				this->handleUndo();
				break;
			case 9:
				std::cout << "Goodbye!" << std::endl;
				return;
			default:
				std::cout << "Invalid option! Try again" << std::endl;
				break;
		}

		this->printMenu();

		std::cout << "Enter option: "; std::cin >> option;
		std::cout << std::endl;
	}
}