#include <iostream>
#include <string>
using namespace std;

int doOperation(char operation[]);

void birdSpeech(char inputStr[], int size, char outputStr[]); // we need to return a char array, but to do that we need to use pointers
// one solution is to provide the output array as a parameter

void primeDecomposition(int no, char outputStr[]);

int main() {
	cout << "Tasks:" << endl;
	cout << "1. Provide a mathmatical operation using only + or - and return the result" << endl;
	cout << "2. Convert text to bird speech" << endl;
	cout << "3. Provide into a string the prime decomposition of a number" << endl;

	int option;
	cout << "Provide the option: ";
	cin >> option;
	while (true) {
		switch (option) {
		case 1: {
			char operation[50];
			cout << "Provide the operation (at most 50 characters): ";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin.getline(operation, 50);
			int res = doOperation(operation, strlen(operation));
			cout << "The result is: " << res << endl;
			break;
		}
		case 2: {
			char sentence[50];
			cout << "Provide the sentence (at most 50 characters): ";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin.getline(sentence, 50);
			char outputStr[150] = { 0 };
			birdSpeech(sentence, strlen(sentence), outputStr);
			cout << "The bird speech sentence is: " << outputStr << endl;
			break;
		}
		case 3: {
			int no;
			cout << "Enter the number to be decomposed into prime factors: ";
			cin >> no;
			char primeDecompositionStr[100];
			primeDecomposition(no, primeDecompositionStr);
			cout << "The prime factors are: " << primeDecompositionStr << endl;
			break;
		}
		case 4:
			cout << "Goodbye!";
			return 0;
		default:
			cout << "Wrong input! Try again." << endl;
			break;
		}
		cout << "Provide the task number or 4 to exit: ";
		cin >> option;
	}
	return 0;
}

int doOperation(char operation[]) {
	// initialize variables
	int firstOp, secondOp, i, j;
	char copyOp[50] = { 0 }; // copy of our operation where we remove redundant spaces
	char firstOpChr[25] = { 0 }, secondOpChr[25] = { 0 }, op; // initialize our char arrays with 0s

	int idxCopy = 0; // index for the new string
	for (int k = 0; k < strlen(operation); k++)
		if (strchr("0123456789+-", operation[k]) != nullptr) // ensure that only allowed characters are in
			copyOp[idxCopy++] = operation[k];

	for (i = 0; i < idxCopy; i++) { // copy into a separate char array all the numbers
		if ((copyOp[i] == '+' || copyOp[i] == '-') && i != 0) { // || = or; && = and
			op = copyOp[i]; // save the main operation
			break;
		}
		firstOpChr[i] = copyOp[i];
	}
	firstOpChr[i] = '\0'; // terminate the string containing the first operand
	firstOp = atoi(firstOpChr); // use atoi to convert the string (char[]) to an integer - it knows how to convert negative numbers as well

	// repeat the same for the second operand
	for (j = i + 1; j < idxCopy; j++)
		secondOpChr[j - i - 1] = copyOp[j];
	secondOpChr[j - i - 1] = '\0';
	secondOp = atoi(secondOpChr);

	if (op == '+')
		return firstOp + secondOp;
	else
		return firstOp - secondOp;
	
}

void birdSpeech(char inputStr[], int size, char outputStr[150]) {
	int j = 0; // index for our return string
	for (int i = 0; i < size; i++) {
		outputStr[j++] = inputStr[i]; // this line attributes inputStr[i] to res[j] and then does j = j + 1
		if (strchr("aeiouAEIOU", inputStr[i]) != nullptr) { // strchr returns the first occurence of the second parameter in the first one
			// this effectively checks whether our current element is a vowel
			outputStr[j++] = inputStr[i] < 0x60 ? 'P' : 'p'; // 0x61 is the ascii code for 'a'; in the ascii table uppercase letter are before the lowercase ones
			// thus, if our character's ascii code is lower than that value, it means it is uppercase and we put an uppercase 'P', otherwise we use a lowercase one
			outputStr[j++] = inputStr[i];
		}
	}
}

void primeDecomposition(int no, char outputStr[]) {
	int j = 0; // index for output string
	int copyNo = no; // copy of our original number so the condition in the for loop doesn't change upon changes to the number
	for (int i = 2; i * i <= copyNo; i++) { // iterate over possible divisors, up to sqrt(no)
		if (no % i == 0) { // if we found a divisor
			int ctr = 0; // counter = power of the factor
			while (no % i == 0) { // divide it as many times as possible
				no /= i; // no = no / i; // similar operators for +, -, * and bit operations (& - and, | - or, ^ - xor) => +=, -=, *=, &=, |=, ^=
				ctr++;
			}

			for (char element : to_string(i)) // convert the divisor to string via to_string function, it takes an int and produces the string representation of it (12 => "12")
				outputStr[j++] = element; // add it to our output string

			outputStr[j++] = '^'; // add the power symbol

			for (char element : to_string(ctr)) // repeat the same procedure for the power itself
				outputStr[j++] = element;

			// add multiplication sign
			outputStr[j++] = ' ';
			outputStr[j++] = '*';
			outputStr[j++] = ' ';
		}
	}

	if (no > 1) { // if there's still a prime factor left, i.e. the original number was prime or it has a divisor bigger than its sqrt
		for (char element : to_string(no)) // build the string with our initial number
			outputStr[j++] = element;
		outputStr[j++] = '^';
		outputStr[j++] = '1';
		outputStr[j] = '\0'; // terminate the string
	}
	else
		outputStr[j - 3] = '\0';  // terminate the string and remove end spaces and * signs
}