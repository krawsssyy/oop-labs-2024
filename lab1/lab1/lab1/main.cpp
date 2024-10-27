#include <iostream>
using namespace std;
#define N 5 // we define the size of the arrays as a constant so we don't use pointers - those will be in the next lab
// #define is a preprocessor statement which allows us to give some value to certain literals
// can be used in the way we did it, or to define small functions, more on that will be in later labs

bool isPrime(int n); // we define the function signature (returnType functionName(param1,...,paramN)) here so we can define the actual function after main
// bool is a data type which has 2 values, false or true and can be used to define values of truth
// int is an integer type, meaning it represents some numerical values
// int by itself is by default signed (accepts negative values as well), if we want to make it unsigned, we have to explicitly do it as such "unsigned int n;"

void sort(int list[], int size);
// void is a data type which means nothing, in our case, the function returns void, meaning that it doesn't return anything
// in our parameters, we send the array "list" by value, but since it is an array, it is always passed by reference, meaning that the function can actually modify the values inside
// for simple types, passing by reference would look like "void func(int &param)"; this allows the function to modify the actual value of "param", else it wouldn't be able
// for arrays, we can either specify their size in the parameter list as such "int list[50]", or leave the size empty and specify it as a different paramter

int countSpaces(char sentence[], int size);

int fibonacci(int n);

int fibonacci_recursive(int n);

int factorial(int x);

int factorial_recursive(int x);


int main() {
	cout << "Tasks: " << endl; // endl = endline - inserts a '\n' character after the text provided
	// cout - used for printing output to the console, you can use it to print variables or strings, or a combination of them
	// cout << "var1=" << var1 << "; var2=" << var2 << endl; - for e.g.
	cout << "1. Check whether a given number is prime" << endl;
	cout << "2. Sort an array" << endl;
	cout << "3. Count the amount of spaces in a given sentence" << endl;
	cout << "4. Provide the n-th Fibonacci number" << endl;
	cout << "5. Calculate the factorial of a given number" << endl;

	int option = 0;
	cout << "Input task to solve: ";
	cin >> option;
	while (true) { // infinite loop
		// brackets are required for code blocks that have more than one statement, else, they can be omitted
		switch (option) { // the switch instruction is like a glorified if sequence, it simplifies that and makes it more readable
			// the following switch statement is equivalent with if(option == 1) ....; else if (option == 2) ... else if (option == 6) ... else ...
			case 1:
				cout << "Input number to check: ";
				int prime;
				cin >> prime;
				if (isPrime(prime))
					cout << "The given number is prime!" << endl;
				else
					cout << "The given number is composite!" << endl;
				// this is an if statement, it allows us to check for certain conditions, and, if they are true, we can execute specific code
				// the else branch is executed if the condition in the if clause evaluates to false
				break; // this is added on each case to tell the computer to stop case testing after and break out of the switch statement
			case 2:
				cout << "Input the 5 elements of the array (press enter after each one or use spaces as a separator): " << endl;
				int list[N]; // this is a list of the int type, meaning that it holds N values of the type it
				// indexing starts from 0, and goes up to N - 1
				// elements are accesible by using square brackets, as such "list[0]", ..., "list[n]"
				for (int i = 0; i < N; i++)
					cin >> list[i];
				// the cin operator is used to read a value into the specified element
				// it will read the type of the provided element
				// that is a for statement, it allows us to iterate over given quantities
				// the syntax of for is "for(initialization stage; stop condition; increment/decrement stage)"
				// in our case, it initializes the "for" variable "i" with a value of 0, which is incremented by 1 after each stage, and stops when i stops being less than N, meaning i = N
				sort(list, N);
				for (int i = 0; i < N; i++)
					cout << list[i] << " ";
				// this for can also be defined as a for each, with the syntax "for (type elementVariable:array)", and it will traverse the array, providing the current element in the variable we have defined
				// thus, we can re-write the above for as such
				// for (int element:list)
				//		cout << element << " ";
				cout << endl;
				break;
			case 3:
				cout << "Write the sentence (maximum of 100 characters): ";
				cin.ignore(numeric_limits<streamsize>::max(), '\n');  // used to clear the input caches as to not receive artifacts when reading
				// this is to be used only when we want to use cin.getline(charArray, length) and we have used cin >> before, and it leaves a trailing '\n' in the input buffer which will be read by getline
				char sentence[100];
				// char is a data type which holds character literals
				// characters are represented by their ascii codes
				// similar to ints, chars are signed by default
				// they are a single byte in size
				cin.getline(sentence, 100); // reads at most 100 characters into our array
				// this is to be used when our sentence has whitespaces (' '), as just doing cin >> sentence would stop at the first space character
				// after our sentence is inputted, a '\0' character will be added at the end to mark the end of the array (character terminator element)
				cout << "The given sentence has " << countSpaces(sentence, strlen(sentence)) << " spaces." << endl;
				break;
				// strlen is a function that provides the length of a character array, by iterating over it until it reaches '\0'
			case 4:
				cout << "Enter the index (n >= 3): ";
				int fibo;
				cin >> fibo;
				int opt;
				cout << "Input 1 for recursive variant and 0 for normal one: ";
				cin >> opt;
				if (opt == 0)
					cout << "The requested Fibonacci number is " << fibonacci(fibo) << endl;
				else if (opt == 1)
					cout << "The requested Fibonacci number is " << fibonacci_recursive(fibo) << endl;
				else
					cout << "Wrong input! Try again." << endl;
				break;
			case 5:
				cout << "Enter the number: ";
				int fact;
				cin >> fact;
				int opt2; // we need to define it as "opt2" and not "opt" since we'll get a redefinition error
				// the values define in the switch statement have local scope, but local to the switch, thus using "opt" would have redefined a variable which is prohibited
				cout << "Input 1 for recursive variant and 0 for normal one: ";
				cin >> opt;
				if (opt == 0)
					cout << "The requested factorial value is " << factorial(fact) << endl;
				else if (opt == 1)
					cout << "The requested factorial value is " << factorial_recursive(fact) << endl;
				else
					cout << "Wrong input! Try again." << endl;
				break;
			case 6:
				cout << "Goodbye!";
				return 0;
			default: // case when none options match
				cout << "Invalid option! Try again." << endl;
				break;
		}
		cout << "Input task to solve or 6 to exit: ";
		cin >> option;
	}
	
	return 0;
}

bool isPrime(int n) { // now that we defined the function signature above main, we now have to define the function itself, with the same signature as before
	if (n <= 1) // base case, n = 1 is not prime, and primes are not defined for negative integers
		return false;
	if (n == 2) // base case, n = 2 is prime
		return true;

	for (int i = 2; i * i <= n; i++) // we need to check only up to sqrt(n) for possible divisors
		if (n % i == 0) // % is the modulo operator, it provides the remainder of the division; if the remainder is 0, it means that the given value is a divisor of the provided number
			return false; // if that is the case, meaning that we found a divisor (apart from 1 and the number itself), it means that the number is not prime
	
	return true; // if we haven't returned from the function until this point, it means that no divisor were found, and the number is prime
}

void sort(int list[], int size) {
	// we will do a simple sorting algorithm
	// we will use 2 for statements to iterate through the given array, and if we find values which are not arranged properly, we swap them
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			if (list[i] > list[j]) {
				int auxValue = list[i];
				list[i] = list[j];
				list[j] = auxValue;
			}
}

int countSpaces(char sentence[], int size) {
	int counter = 0; // we initialize the counter to 0
	// we will traverse the char array and check at every point if the current element is ' '
	for (int i = 0; i < size; i++)
		if (sentence[i] == ' ')
			counter++; // counter++ is equivalent to "counter = counter + 1;"
	// counter++ is the postfix variant of the '++" operator, which means that it first uses the value of counter for whatever it needs to do, and then increments it
	// in our case, it doesn't matter whether we do ++counter or counter++, but it other cases it might
	return counter;
}

int fibonacci(int n) {
	if (n < 1) // base case, if n is smaller than 1, we return 0 as it is not defined
		return 0;
	if (n < 3) // if the user requested one of the first two fibonacci numbers, return it
		return 1;

	int prev = 1, prevprev = 1, current;
	// F_1 = 1, F_2 = 1, F_n = F_(n-1) + F_(n-2) for all n >= 3, with n being an integer
	for (int i = 0; i < n - 2; i++) { // we are going up to n - 2 since we already have the first 2 numbers
		current = prev + prevprev; // F_n = F_(n-1) + F_(n-2)
		prevprev = prev; // F_(n-2) = F_(n-1)
		prev = current; // F_(n-1) = F_n
	}
	return current;
}

int fibonacci_recursive(int n) {
	if (n < 1) // base case handling, ensuring that the input is always bigger than or equal to 3
		return 0;
	if (n == 2 || n == 1) // handling F_2 and F_1
		return 1;
	return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2);
	// recursively call the function to build up the sum
}


int factorial(int x) {
	if (x < 0) // factorial is not defined for negative values
		return 0;

	int value = 1; // since we will be doing products, we have the initial value = 1 (also, 0! = 1)
	// x! = x * (x - 1) * (x - 2) * ... * 3 * 2 * 1
	for (int i = 2; i <= x; i++)
		value = value * i;
	return value;
}

int factorial_recursive(int x) {
	if (x < 0) // check for negative values
		return 0;
	return x == 1 ? 1 : x * factorial_recursive(x - 1);
	// that is called the ternary operator
	// it has the following syntax: "condition ? trueBranch : falseBranch;"
}