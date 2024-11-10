#pragma once
#include "Service.h"

class Console {
	private:
		Service& s;
		void printMenu();
		void handleAdd();
		void handleUpdate();
		void handleRead();
		void handleDelete();
		void handleBorrow();
		void handleReturn();
		void handleShow();
		void handleUndo();
	public:
		Console(Service& s) : s(s) {}
		~Console() {}
		void run();
};