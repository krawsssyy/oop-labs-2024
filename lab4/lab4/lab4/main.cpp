#define _CRT_SECURE_NO_WARNINGS // for strcpy, since we ensured prior that the buffer holds our copy
#include <iostream>
using namespace std;

enum CAR_TYPE {GAS, DIESEL, HYBRID, ELECTRIC}; // this is an enum data type
// it allows us to map numerical values to some predefined constants more easily
// for e.g., for an enum like this, GAS will be 0, DIESEL will be 1, and so on
// we can then use those literals we defined for easier checks and processing

class Car {
	private: // private attribute, meaning that it won't be accessible outside of the class definition/declaration, by any means
		char* engineSerial;
	public: // public members, can be accessed outside the class via the "." operator
		int yearOfFabrication;
		long long numKMs; // since it can be a big number, it needs to be long long
		int engineCapacity;
		int horsepower;
		string color;
		float price;
		enum CAR_TYPE gasType;

		Car() { // define the non-parametrized constructor
			// it will be called when we instantiate the class as such: Car a = Car(); -- without any parameters
			// it defines the default values our members should take
			this->yearOfFabrication = this->numKMs = this->engineCapacity = this->horsepower = 0; // equivalent to setting each of these to 0
			this->color = "";
			this->price = 0.f; // when using 5., or 4., it tells C++ that this value is a double, hence it saves 5.0, 4.0 respectively
			// adding the f after the number tells it is a float
			this->gasType = GAS; // we also could have done gasType = (CAR_TYPE)0; -- we cast the 0 value to the respective value from the enum, meaning GAS
			this->engineSerial = new char[15]; // initialize dynamic memory
			memset(this->engineSerial, 0, 16 * sizeof(char)); // set it to all 0s (NULLs)

			// this is a special pointer in classes
			// it represents the current class, and it points to the current object, whatever that may be
			// when we do Car a = Car(); -- it will enter this constructor, and this will point to the memory address of the variable "a"
			// when we do Car b = Car(); -- it will enter this constructor, and this will point to the memory address of the variable "b" now (it always points to the object at hand)
			// thus, we use it to refer to the current object, and it is good to always use it in when we refer to the members of a class
		}

		Car(const char* engineSerial, int yearOfFabrication, int numKMs, int engineCapacity, int horsepower, string color, float price, enum CAR_TYPE gasType) {
			// this is a paremetrized constructor
			// it allows us to define the values that the attributes take upon initialization of the object
			// it is called similar to the non-parametrized version, just that we add the parameters
			this->yearOfFabrication = yearOfFabrication;
			this->numKMs = numKMs;
			this->engineCapacity = engineCapacity;
			this->horsepower = horsepower;
			this->color = color;
			this->price = price;
			this->gasType = gasType;

			this->engineSerial = new char[strlen(engineSerial) + 1];
			strcpy(this->engineSerial, engineSerial); // copy the value given into our pointer
		}

		Car(const Car& car) {
			// this is a copy constructor
			// it allows us to define an object, based on the values of another object
			// Car a = Car(...); Car b = Car(a); -- it will have same values as the "car a"
			this->yearOfFabrication = car.yearOfFabrication;
			this->numKMs = car.numKMs;
			this->engineCapacity = car.engineCapacity;
			this->horsepower = car.horsepower;
			this->color = car.color;
			this->price = car.price;
			this->gasType = car.gasType;
			// private members of the class can be access via "." operator in a copy constructor, since is the class itself using them
			// otherwise, we need to use getters/setters
			this->engineSerial = new char[strlen(car.engineSerial) + 1];
			strcpy(this->engineSerial, car.engineSerial);

		}

		void setEngineSerial(const char* engineSerial) { // setter for the engine serial
			if (this->engineSerial) { // delete old pointer if the engineSerial is set
				delete[] this->engineSerial;
				this->engineSerial = NULL;
			}

			this->engineSerial = new char[strlen(engineSerial) + 1];
			strcpy(this->engineSerial, engineSerial);
		}

		char* getEngineSerial() { // getter for the engine serial
			// return a copy of our pointer, such that it can't be modified
			char* copy = new char[strlen(this->engineSerial) + 1];
			strcpy(copy, this->engineSerial);
			return copy;
			// it will have to be deallocated by the user after its done with it
		}

		void setYearOfFabrication(int yearOfFabrication) { // setter for the year of fabrication
			this->yearOfFabrication = yearOfFabrication;
		}

		int getYearOfFabrication() { // getter for the year of fabrication
			return this->yearOfFabrication;
		}

		void setNumKMs(long long numKMs) { // setter for the number of kilometers
			this->numKMs = numKMs;
		}

		long long getNumKMs() { // getter for the number of kilometers
			return this->numKMs;
		}

		void setEngineCapacity(int engineCapacity) { // setter for the engine capacity
			this->engineCapacity = engineCapacity;
		}

		int getEngineCapacity() { // getter for the engine capacity
			return this->engineCapacity;
		}

		void setHorsepower(int horsepower) { // setter for the horsepower
			this->horsepower = horsepower;
		}

		int getHorsepower() { // getter for the horsepower
			return this->horsepower;
		}

		void setColor(string color) { // setter for the color
			this->color = color;
		}

		string getColor() { // getter for the color
			return this->color;
		}

		void setPrice(float price) { // setter for the price
			this->price = price;
		}

		float getPrice() { // getter for the price
			return this->price;
		}

		void setGasType(enum CAR_TYPE gasType) { // setter for the gas type
			this->gasType = gasType;
		}

		enum CAR_TYPE getGasType() { // getter for the gas type
			return this->gasType;
		}

		void prettyDisplay(bool showSerial) {
			cout << "Current car: " << endl;
			cout << "Year of fabrication: " << this->yearOfFabrication << endl; // we could have as well used the getter functions
			// instead of this->yearOfFabrication, we would have this->getYearOfFabrication(), and it would have been the same
			// when calling functions inside the class, we still use the this pointer to refer to them
			cout << "Engine capacity: " << this->engineCapacity << " cm^3" << endl;
			cout << "Number of kilometers: " << this->numKMs << endl;
			cout << "Horsepower: " << this->horsepower << endl;
			cout << "Price: " << this->price << endl;
			cout << "Color: " << this->color << endl;
			cout << "Type: ";

			switch (this->gasType) {
				case GAS:
					cout << "GAS" << endl;
					break;
				case DIESEL:
					cout << "DIESEL" << endl;
					break;
				case HYBRID:
					cout << "HYBRID" << endl;
					break;
				case ELECTRIC:
					cout << "ELECTRIC" << endl;
					break;
			}

			if (showSerial) // switch to determine whether we show the serial number of the engine or not
				cout << "Serial number: " << this->engineSerial << endl;

			cout << endl;
		}

		~Car() { // destructor
			// special function, that is not called by us, but is called automatically when the variable finishes its scope
			// think of a variable scope as the "{" "}" block it which it was defined
			// when that instruction block ends, the variable is destroyed
			// if we have a pointer to our class, as such: Car* a = new Car(); -- when doing "delete Car;", this will call the destructor, but apart from this case, we have no way of calling it manually
			// it is used to clean up the memory and special variables used by our class

			if (this->engineSerial) { // ensure it is set
				delete[] this->engineSerial;
				this->engineSerial = NULL; // cleanup for the dynamic memory
			}
		}

};

int main() {
	Car a; // leaving it as such will call the non-parametrized constructor, hence it will have default values
	// equivalent to Car a = Car();
	a.prettyDisplay(true);

	Car b("IRTM109231239123", 2002, 170128, 2000, 175, "red", 50000.5f, GAS); // this is equivalent to Car b = Car(....);
	b.prettyDisplay(true);

	Car c(b); // equivalent to Car c = Car(b);
	c.prettyDisplay(true);

	c.setColor("blue");
	c.setGasType((CAR_TYPE)3);
	c.setYearOfFabrication(2017);
	c.setNumKMs(40001);
	c.setPrice(95129.8f);
	c.setHorsepower(250);
	c.prettyDisplay(false);

	return 0;
}