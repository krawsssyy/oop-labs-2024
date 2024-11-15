#pragma once
#include "Supervisor.h"

class RepositorySupervisor {
	private:
		Supervisor** list;
		int size;
		int capacity;
	public:
		RepositorySupervisor() {
			this->capacity = 100;
			this->list = new Supervisor * [capacity];
			memset(this->list, 0, sizeof(Supervisor*) * this->capacity);
			this->size = 0;
		}

		~RepositorySupervisor() {
			for (int i = 0; i < this->capacity; i++)
				delete this->list[i];
			delete[] this->list;
			this->list = nullptr;
		}

		void resize(int newSize) {
			Supervisor** newElems = new Supervisor * [newSize];
			memset(newElems, 0, sizeof(Supervisor*) * newSize);
			memcpy(newElems, this->list, sizeof(Supervisor*) * this->capacity);

			this->capacity = newSize;
			delete[] this->list;
			this->list = newElems;
		}

		void addElement(Supervisor* elem) {
			if (this->size + 1 >= this->capacity)
				this->resize(this->capacity + 10);

			this->list[this->size++] = elem;
		}

		void updateElement(int ID, Supervisor* elem) {
			for (int i = 0; i < this->size; i++)
				if (this->list[i]->getID() == ID) {
					delete this->list[i];
					this->list[i] = elem;
					return;
				}
		}

		void deleteElement(int ID) {
			int idx = -1;
			for (int i = 0; i < this->size; i++)
				if (this->list[i]->getID() == ID) {
					idx = i;
					break;
				}

			if (idx == this->size - 1) {
				this->size--;
				delete this->list[idx];
			}
			else {
				delete this->list[idx];
				for (int i = idx; i < this->size - 1; i++)
					this->list[i] = this->list[i + 1];
				this->size--;
			}
			// no need for checks if the index doesn't exist since we check that in the service
		}

		Supervisor* readElement(int ID) {
			for (int i = 0; i < this->size; i++)
				if (this->list[i]->getID() == ID)
					return this->list[i];

			return nullptr;
		}

		int getSize() { return this->size; }

		Supervisor** getAll() {
			return this->list;
		}
};