#pragma once
#include "Book.h"

class Stack { // this is a custom implementation of a stack (LIFO principle - Last In, First Out)
	private:
		size_t size;
		size_t capacity;
		Book*** stack; // we will save the list of entities (which is Book**), thus the Book***
		// after each operation on the repo (except for the read one), we will save our list of entities in this stack
		// when an undo is to be done, we just get the last element and set it as our list of entities
		// using this, we can also do a redo operation, by having two stacks, one for the undo and one for the redo
		// when we do an undo, we put the current list of entities into the redo stack, and vice versa for the redo
		size_t* sizes;
		void resize(int newSize);
	public:
		Stack();
		~Stack();
		Book** pop();
		void push(Book** element, size_t size);
		size_t getSize();
		size_t getListSize();
};