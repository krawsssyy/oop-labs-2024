#include "Service.h"

void Service::addBook(std::string title, std::string author, std::string ISBN, std::string publisher, int year, bool borrowed) {
	this->s->push(this->r.getAll(), this->r.getSize()); // add the current list of elements to our undo stack

	Book* b = new Book(title, author, ISBN, publisher, year, borrowed);
	this->r.addElement(b);
}

bool Service::updateBook(std::string origISBN, std::string title, std::string author, std::string ISBN, std::string publisher, int year, bool borrowed) {
	if (this->r.readElement(origISBN) == nullptr)
		return false;

	this->s->push(this->r.getAll(), this->r.getSize());

	Book* b = new Book(title, author, ISBN, publisher, year, borrowed);
	this->r.updateElement(origISBN, b);
	return true;
}

Book* Service::readBook(std::string ISBN) {
	return this->r.readElement(ISBN);
}

bool Service::deleteBook(std::string ISBN) {
	if (this->r.readElement(ISBN) == nullptr)
		return false;

	this->s->push(this->r.getAll(), this->r.getSize());

	this->r.deleteElement(ISBN);
}

Book** Service::getAll() {
	return this->r.getAll();
}

size_t Service::getSize() {
	return this->r.getSize();
}

bool Service::isBorrowed(std::string ISBN) {
	if (this->r.readElement(ISBN) == nullptr)
		return false; // we don't have a way to distinguish between not borrowed and non existent book yet

	return this->r.readElement(ISBN)->getBorrow();
}

bool Service::borrow(std::string ISBN) { // dual function, if the book is borrowed it marks it as returned, if it is not it borrows it
	if (this->r.readElement(ISBN) == nullptr)
		return false;

	this->s->push(this->r.getAll(), this->r.getSize());

	this->r.readElement(ISBN)->changeBorrow();
	return true;
}

bool Service::undo() {
	if (!this->s->getSize())
		return false;

	Book** value = this->s->pop();
	size_t size = this->s->getListSize();
	this->r.setVector(value, size);
	return true;
}