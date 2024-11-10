#include "Repository.h"

Repository::Repository(){
	this->size = 0; // set an initial size and capacity
	this->capacity = 100;
	this->elements = new Book*[this->capacity];
	memset(this->elements, 0, sizeof(Book*) * this->capacity);
}

Repository::~Repository() {
	// cleanup
	for (int i = 0; i < this->getSize(); i++)
		delete this->elements[i];
	delete[] this->elements;
	this->elements = nullptr;
}

void Repository::addElement(Book* elem) {
	if (this->size + 1 >= this->capacity) // if we reached the end, resize the array
		this->resize(capacity + 10);

	this->elements[this->size++] = elem;
}

void Repository::updateElement(std::string ISBN, Book* elem) {
	for (int i = 0; i < this->size; i++) 
		if (this->elements[i]->getISBN() == ISBN) {
			delete this->elements[i]; // delete old value
			this->elements[i] = elem;
			return;
		}
}

void Repository::deleteElement(std::string ISBN) {
	int idx = 0;
	for (int i = 0; i < this->size; i++)
		if (this->elements[i]->getISBN() == ISBN) {
			idx = i;
			break;
		}

	if (idx == this->size - 1) {
		this->size--;
		delete this->elements[idx];
	}
	else {
		delete this->elements[idx];

		for (int i = idx; i < this->size - 1; i++)
			this->elements[i] = this->elements[i + 1];
		this->size--;
	}
}

Book* Repository::readElement(std::string ISBN) {
	for (int i = 0; i < this->size; i++)
		if (this->elements[i]->getISBN() == ISBN)
			return this->elements[i];

	return nullptr;
}

size_t Repository::getSize() {
	return this->size;
}

Book** Repository::getAll() {
	Book** cpy = new Book*[this->capacity];
	memset(cpy, 0, sizeof(Book*) * this->capacity);

	for (int i = 0; i < this->size; i++)
		cpy[i] = new Book(this->elements[i]);

	return cpy; // return a copy
}

void Repository::resize(int newSize) {
	Book** newElems = new Book*[newSize];
	memset(newElems, 0, sizeof(Book*) * newSize);
	memcpy(newElems, this->elements, sizeof(Book*) * this->capacity);

	this->capacity = newSize;
	delete[] this->elements;
	this->elements = newElems;
}

void Repository::setVector(Book** elements, size_t size) { // function to change the list of books, to be used in service for undo

	// clean our array, since the new one will be a copy, we are not deleting anything we will use
	for (int i = 0; i < this->size; i++) {
		delete this->elements[i];
		this->elements[i] = nullptr;
	}
	delete[] this->elements;

	this->elements = elements;
	this->size = size;
}
