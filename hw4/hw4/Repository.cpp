#include "Repository.h"

Repository::Repository() {
	this->size = 0; // set an initial size and capacity
	this->capacity = 100;
	this->elements = new Patient*[this->capacity];
}

Repository::~Repository() {
	// cleanup
	for (int i = 0; i < this->getSize(); i++)
		delete this->elements[i];
	delete[] this->elements;
	this->elements = nullptr;
}

void Repository::addElement(Patient* elem) {
	if (this->size + 1 >= this->capacity) // if we reached the end, resize the array
		this->resize(capacity + 10);

	this->elements[this->size++] = elem;
}

void Repository::updateElement(std::string CNP, Patient* elem) {
	for (int i = 0; i < this->size; i++) // std::vector has no .length() function, but it has .size() which here returns the actual length of the vector, and not the size in bytes
		if (this->elements[i]->getCNP() == CNP) {
			// we use the CNP as an identifier
			this->elements[i] = elem;
			return;
		}
}

void Repository::deleteElement(std::string CNP) {
	int idx = 0; // variable that will determine the index for deletion
	for (int i = 0; i < this->size; i++)
		if (this->elements[i]->getCNP() == CNP) {
			idx = i;
			break;
		}

	if (idx == this->size - 1) // if we have to delete the last element
		this->size--; // we just decrease the size, essentially allowing for an overwrite and not taking that element into account
	else {
		for (int i = idx; i < this->size - 1; i++)
			this->elements[i] = this->elements[i + 1]; // shift the entire array to the left, so that we delete the element
		this->size--;
	}
}

Patient* Repository::readElement(std::string CNP) {
	for (int i = 0; i < this->size; i++)
		if (this->elements[i]->getCNP() == CNP)
			return this->elements[i]; // return the actual object

	return nullptr; // return null if not found
}

size_t Repository::getSize() {
	return this->size;
}

Patient** Repository::getAll() {
	return this->elements;
}

void Repository::resize(int newSize) {
	Patient** newElems = new Patient*[newSize];

	memcpy(newElems, this->elements, sizeof(Patient*) * this->capacity); // no checks since we will be only be resizing up
	// since we hold pointers, we get the size of the pointer
	this->capacity = newSize;
	delete[] this->elements;
	this->elements = newElems;
}
