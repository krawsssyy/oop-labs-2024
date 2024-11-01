#pragma once
#include <string>


// custom implementation for a pair
class Pair {
public:
	std::string first, second;
	Pair() = default; // tells C++ that it is a default constructor, and that all class members should be initialized with their default values according to the type
	Pair(std::string first, std::string second) : first(first), second(second) {} // small constructor
};
