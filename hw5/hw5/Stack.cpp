#include "Stack.h"

Stack::Stack() {
	this->size = 0;
	this->capacity = 100;
	this->stack = new Book**[this->capacity];
	memset(this->stack, 0, sizeof(Book**) * this->capacity);
	this->sizes = new size_t[this->capacity];
	memset(this->sizes, 0, sizeof(size_t) * this->capacity);
}

Stack::~Stack() {
	// since we'll add copies, we have to deallocate each one
	for (int i = 0; i < this->size; i++) {
		for (int j = 0; j < this->sizes[i]; j++) {
			delete this->stack[i][j];
			this->stack[i][j] = nullptr;
		}
		delete[] this->stack[i];
		this->stack[i] = nullptr;
	}

	delete[] this->stack;
	this->stack = nullptr;

	delete[] this->sizes;
	this->sizes = nullptr;
}

void Stack::resize(int newSize) {
	Book*** newStack = new Book**[newSize];
	memset(newStack, 0, sizeof(Book**) * newSize);
	memcpy(newStack, this->stack, sizeof(Book*) * this->capacity);

	delete[] this->stack;
	this->stack = newStack;

	size_t* newSizes = new size_t[newSize];
	memset(newSizes, 0, sizeof(size_t) * newSize);
	memcpy(newSizes, this->sizes, sizeof(size_t) * this->capacity);

	this->capacity = newSize;

	delete[] this->sizes;
	this->sizes = newSizes;
}

void Stack::push(Book** element, size_t size) {
	if (this->size + 1 >= this->capacity)
		this->resize(this->capacity + 10);

	this->stack[this->size] = element;
	this->sizes[this->size++] = size;
}

Book** Stack::pop() {
	if (this->size == 0)
		return nullptr; // if the stack is empty, return null

	Book** ret = this->stack[--this->size];
	this->stack[this->size] = nullptr; // prevent dangling pointers

	return ret;
}

size_t Stack::getSize() {
	return this->size;
}

size_t Stack::getListSize() {
	return this->sizes[this->size];
}