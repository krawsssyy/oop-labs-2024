#include <iostream>
#include <string> // for getline
#include <fstream> // for ifstream
using namespace std;

string* permutations; // global variables so we can use them all throughout
// it will hold all the permutatiions
int permutationsIdx; // the index in the permutation array
// it being a global variable, it is initialized with 0
// all global variables are initialized with their type's default (i.e. the non-parametrized constructor is called, more on that when doing classes)

int factorial(int num) { // helper function
	if (num < 0)
		return 0;

	if (num <= 1)
		return 1;

	int product = 1;
	for (int i = 2; i <= num; i++)
		product *= i;

	return product;
}


void generatePermutations(string word, int permutationIdx) {

	if (permutationIdx == word.length()) { // if we created a word of the desired length (i.e. we permuted the last character of the string), add it to our permutations array and exit this branch, since we are done
		permutations[permutationsIdx++] = word;
		return;
	}
	
	for (int i = permutationIdx; i < word.length(); i++) { // loop where all the permutations happen
		char aux = word[permutationIdx]; // swap two characters around
		word[permutationIdx] = word[i];
		word[i] = aux;

		generatePermutations(word, permutationIdx + 1); // recursive call to generate the permutations, permuting now the next position in the string
		// this effectively fixes the first letter (at the first step), then goes on to permute the next letter, then fixes the second letter and permutes the third, and so on
		// the same procedure is done for all letters
		// one by one, a letter is fixed in a position and the rest are permuted

		aux = word[permutationIdx]; // swapping them back, which constitutes the backtracking part
		word[permutationIdx] = word[i]; // after we've done all permutations with that letter fixed in that position, we now go back and move on to the next letter
		word[i] = aux; // we fix it in that position, and do the whole procedure once again
	}

	// when we'll learn about stl, we'll see that we can do this far simpler, as such
	/*
	#include<algorithm>
	...
	...
	do {
		cout << word << endl;
	} while (next_permutation(word.begin(), word.end())); // STL function for generating permutations of the given array based on the type of the iterator given
	*/

}

string lccs(string first, string second) { // longest common consecutive substring
	int firstSize = first.length(); // .size() works as well in our case, given this is a string
	// length returns the number of elements, whereas size returns the number of bytes for this
	// since characters are 1 byte, length() and size() yield the same result for a STRING
	int secondSize = second.length();

	int maxSSLength = 0; // variable that keeps track of the maximum length of a substring
	int matchIdx = 0; // variable to keep track where the match occured (can be from the first string or the second, doesn't really matter since they both will contain that substring)

	for (int i = 0; i < firstSize; i++) // traverse the first string
		for (int j = 0; j < secondSize; j++) { // traverse the second string
			int currLength = 0; // current length of the substring

			while (i + currLength < firstSize && j + currLength < secondSize && first[i + currLength] == second[j + currLength])
				// ensure that we are within the bounds of the words
				// and keep going as many times as we find matching characters
				currLength++;

			if (currLength > maxSSLength) { // if we found a match that it is bigger in length than our maximum
				maxSSLength = currLength; // update our maximum length
				matchIdx = i; // save the starting position of the matching substring
			}
		}

	if (maxSSLength) // if we found a match
		return first.substr(matchIdx, maxSSLength); // substr() for a string returns a substring starting at the position given by the first parameter, with the length specified in the second parameter
	
	return ""; // if no match was found, return an empty string
}

int main() {
	cout << "1. Generate all permutations of a string" << endl;
	cout << "2. LCS of two strings" << endl;
	cout << "3. From a list of students and their grades, show who's passing" << endl;

	int option;
	cout << "Enter task (or 4 to exit): ";
	cin >> option;
	
	while (true) {
		switch (option) {
			case 1: {
				string word;
				cout << "Enter word: ";
				cin >> word; // we use cin since we read just a word, hence we don't care about reading spaces

				int size = factorial(word.length()); // length() function for strings works the same as strlen for char
				permutations = new string[size]; // initialize permutations array

				generatePermutations(word, 0);

				cout << "Displaying all " << size << " permutations:" << endl;
				for (int i = 0; i < size; i++)
					cout << permutations[i] << endl;

				delete[] permutations; // cleanup
				permutations = nullptr;

				break;
			}
			case 2: {
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear cin cache of dangling newlines

				string first, second;
				cout << "Enter first string: ";
				getline(cin, first); // use this to read indefinite amount of characters into a string, including spaces
				// as with regular cin.getline, it stops at '\n' (i.e. enter)
				// getline has the following syntax
				// getline(inputStream, stringVar); 
				// inputStream can be cin or a stringstream or a file stream
				cout << "Enter second word: ";
				getline(cin, second);

				string lccs_result = lccs(first, second); // obtain lccs
				if (lccs_result == "")
					cout << "No matching consecutive substring were found!" << endl;
				else
					cout << "Longest common consecutive substring is: " << lccs_result << endl;

				break;

			}
			case 3: {
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear cin cache of dangling newlines

				string filePath;
				cout << "Enter path of the file (absolute path): ";
				getline(cin, filePath);

				float passingGrade;
				cout << "Enter the passing grade: ";
				cin >> passingGrade;

				ifstream f(filePath); // open the provided file

				if (!f.is_open()) { // check if the file opened properly
					cout << "Error when opening file! Try again." << endl;
					break; // exit the switch case
				}

				string line; // variable that will hold lines read from our file
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear cin cache of dangling newlines
				while (getline(f, line)) { // as long as we have lines in our file, read them
					// this loop will read until EOF (end-of-file)
					int nameEndPos = line.find(","); // find returns the position where the first match for the character we provided occurs
					string studentName = line.substr(0, nameEndPos); // this saves the name of our student in a variable, by obtaining a substring from the start up until the first match of ","
					line.erase(0, nameEndPos + 1); // we erase the line containg the name, as well as the "," character, in order to continue with traversing it for the grades

					float average = 0; // initialize our average
					size_t ctx; // will be used as the context (internal state) of our function for conversion from string to float
					// the function requires it to be size_t
					// size_t is a special datatype that usually holds the sizes of different objects, and as such it is created to hold the maximum possible size of any object
					int pos; // variable that will hold the matching position of the "," in our string
					int noGrades = 0; // count how many grades there are

					while ((pos = line.find(",")) != string::npos) { // string::npos means that the end of the string was reached
						// find returns that when we have no matches
						average += stof(line.substr(0, pos), &ctx); // as we have atoi (ascii to int) for conversion of char* to int, we have the same for strings, specifically stoi (string to int)
						// but since we use floats, we have stof (string to float) - we can also have atof (ascii to float, but it actually returns double rather than float)
						// for strings, we also have stod (string to double), stol (string to long), stoll (string to long long), stold (string to long double), stoul (string to unsigned long), stoull
						// for char*, we can also have atol (ascii to long) and atoll (ascii to long long)
						// for strings, we can also strtol, strtol, strtoll, strtoul, strtoull, strtof, strtod, strtold (these are a bit more special, but feel free to reasearch them)
						line.erase(0, pos + 1); // delete what we've already traversed
						noGrades++; // increment the amount of grades
					}
					average /= noGrades; // divide by the amount of grades

					if (average - passingGrade > numeric_limits<float>::epsilon()) { // numeric_limits<float>::epsilon() returns the "machine epsilon" - a very small number used in comparisons for floats
						// same is valid for doubles - numeric_limits<double>::epsilon()
						// for floating point numbers, it is better to go with this approach, because they can lose precision when doing arithmetic (for e.g. if we did only if (average > passingGrade), there could've been a case where average = 5.000000000001, and the passing grade = 5.00000000, and that if would not return true, due to the loss of precision
						// as such, we compare them with a really really small number, as to ensure they are different, albeit by the slighest of margins
						// if we wanted to check for equality, we'd do as such
						// if (fabs(average - passingGrade) < numeric_limits<float>::epsilon())
						// fabs means floating absolute value, it does |average - passingGrade| and compares it to a predefined value
						// ensuring that they are smaller than that very tiny number assures us that the numbers are almost if not equal
						cout << "Student " + studentName + " passed with grade " + to_string(average) << endl;
					}
				}
				f.close(); // cleanup for the ifstream

				break;
			}
			case 4: {
				cout << "Goodbye!";
				return 0;
			}
			default: {
				cout << "Invalid option! Try again." << endl;
				break;
			}
		}
		cout << "Enter task (or 4 to exit): ";
		cin >> option;
	}

	return 0;
}