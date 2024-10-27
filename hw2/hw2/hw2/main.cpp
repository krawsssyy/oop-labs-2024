#define _CRT_SECURE_NO_WARNINGS // for strtok
#include <iostream>
using namespace std;

int countWords(char* sentence) { // auxiliary function that counts the amount of words from a sentence
	// it was used so we can get the number of words in the sentence from main, such that we have a way to know the length of the frequency map
	int noSpaces = 0; // declare variables
	char* posSpace = sentence; // pos isn't a dynamically allocated pointer, it is just a variable that points (has the address of) somewhere in our string, but wasn't allocated dynamically, hence no cleaning is required here

	while ((posSpace = strchr(posSpace, ' ')) != nullptr) { // count the amount of spaces in the word to determine the amount of words (it will be noSpaces + 1)
		// in conditions for while, do while, if etc.., you can also use them to declare variables and then check their values as was done there
		// the strchr functions finds the first occurence of the char in the second parameter in the char* from the first parameter and returns a pointer to where that occurence happens
		noSpaces++; // increment the amount of spaces
		posSpace++; // move pointer one position after the occurence so we search for spaces after that
	}

	return noSpaces + 1;
}

int** countVowelsPerWord(char* sentence) {
	int noWords = countWords(sentence);

	int** frequencyMap = new int* [noWords]; // declare and initialze our frequency map
	for (int i = 0; i < noWords; i++) {
		frequencyMap[i] = new int[10]; // indexes 0-9 will correspond to a char from the string "aeiouAEIOU" in order
		memset(frequencyMap[i], 0, 10 * sizeof(int)); // initialize all values to 0
	}

	char* token = strtok(sentence, " ");
	// the strtok function splits the char* in the first parameter into tokens delimited by the char* in the second parameter
	// the first call is done using an actual char* as the first parameter
	// subsequent calls are done using nullptr as the first parameter, as the function automatically remembers the end of the previous token returned
	// and will continue scanning from that point onwards
	int wordIdx = 0;
	const char* vowels = "aeiouAEIOU"; // this is not dynamically allocated memory, it wasn't created using "new"; it may use a pointer to reference an array, but is not dynamic (that array was created statically), hence it needs no cleaning
	// this pointer just has the memory address of the statically allocated string

	while (token != nullptr) {
		for (int i = 0; i < strlen(token); i++) { // traverse the token and calculate the frequencies of vowels
			const char* posVowel = strchr(vowels, token[i]); // obtain the position of our vowel in the vowel string (returns a pointer to that occurence)
			if (posVowel != nullptr) // ensure a match was found (meaning our character is a vowel)
				frequencyMap[wordIdx][posVowel - vowels] += 1; // pointer arithmetic
				// by subtracting the pointer (memory address) of our occurence with the base address of the string, we get its offset within the string, i.e. the index of the vowel that was found
				// since our frequency map has its indexes mapped accordingly to the string "aeiouAEIOU", this obtains us the required index we need to increment
		}
		wordIdx++; // increment the counter for the word
		token = strtok(nullptr, " "); // obtain next token
		// token is also not dynamically allocated memory, it is just a pointer to somewhere in our char* and wasn't allocated using "new"
	}

	return frequencyMap; // since we return a pointer, the cleanup will occur in main, after we're done
}

struct Node {
	int value; // the value at the element in the list
	Node* flink; // forward link
	Node* blink; // backward link

	Node(int data) : value(data), flink(nullptr), blink(nullptr) {}
};
// I will implement a circular double-linked list (head->blink = tail and tail->flink = head)
// the regular double-linked list (head->blink = nullptr and tail->flink = nullptr) is a bit simpler, but both variants will be accepted, as no specific variant was specified in the tasks' text

void addNode(Node*& head, Node*& tail, int value, bool toTail) {
	// having the 2 nodes as references as their value can change
	Node* newNode = new Node(value);
	if (head == nullptr)
	{
		head = tail = new Node(value); // if our linked list is empty, initialize both the tail and the head with the new node
		// following two instructions not required when dealing with a regular double-linked list
		head->flink = tail; // both flink and blink will point to itself
		head->blink = tail;
		return;
	}
	else {
		newNode->flink = head; // set the next element of our new element to be the head
		newNode->blink = tail; // set the previous element of our new element to be the tail
		head->blink = newNode; // set the previous element of the head to be our new element
		tail->flink = newNode; // set the next element of the tail to be our new element
		// if we had a regular double-linked list, this would look like this
		// adding to the head
		// newNode->flink = head;
		// head->blink = newNode;
		// head = newNode;
		// adding to the tail
		// newNode->blink = tail;
		// tail->flink = newNode;
		// tail = newNode;
	}

	// this part isn't necessary for a regular double-linked list
	if (toTail) // check whether we want to add to the tail or to the head
		tail = newNode; // if we add to the tail, we now set the tail to be our new element
	else
		head = newNode; // if we want to add to the head, we not set the head to be our new element
}

void traverseForward(Node* head) {
	// ideally we'd want to check here as well whether the head is empty, but we've ensured that we have at least one element
	Node* curr = head; // start from the head forwards
	do {
		cout << curr->value << " "; // print value
		curr = curr->flink; // move to the next element
	} while (curr != head);
	// this is a do while construct, and it differs from the simple while in the fact that "while" checks the condition at the start, and "do while" checks it at the end
	// beware of the ";" that needs to be added after the condition 
	// we used this here as to not handle the head separately and to be able to use our end condition properly
}

void traverseBackward(Node* tail) {
	Node* curr = tail; // start from the tail backwards
	do {
		cout << curr->value << " "; // print value
		curr = curr->blink; // move to the previous element
	} while (curr != tail);
}

void removeNode(Node*& head, Node*& tail, int value) {
	// function not used, but implemented for demonstration purposes
	if (head == nullptr) // if the list is empty exit
		return;

	if (head->value == value) {
		// if the value required is in the head
		if (head == tail) { // if we have only one element in the list
			delete head; // this will delete tail as well since they are the same pointer
			head = tail = nullptr;
		}
		else {
			Node* aux = head;
			head = head->flink; // move the head
			head->blink = tail; // update its blink pointer to point to the tail
			tail->flink = head; // update tail's flink to point to the new head
			delete aux; // delete previous head
		}
		return; // exit
	}

	Node* curr = head; // variable used in traversing the list
	do {
		if (curr->value == value)
			break;
		curr = curr->flink;
	} while (curr != head);

	if (curr == tail) { // if the value required is in the tail
		tail = tail->blink; // move tail to previous element
		tail->flink = head; // update flink pointer
		head->blink = tail; // update head's blink to point to the new tail
		delete curr; // delete the node
		return; // exit
	}

	// else, if it is neither the head nor the tail, we update the respective pointers
	curr->blink->flink = curr->flink; // update the flink pointer of the previous element to point to the next element of the one to be deleted
	curr->flink->blink = curr->blink; // update the blink pointer of the next element to point to the previous element of the one to be deleted
	delete curr; // cleanup
}

/*
* removal of a node from a regular double-linked list
void removeNode(Node*& head, Node*& tail, int value) {
	if (head == nullptr) // if the list is empty, exit
		return;

	if (head->value == value) { // if the value to be deleted is in the head
		Node* aux = head; // save the current head
		head = head->flink; // update the head to point to the next element
		if (head != nullptr) // if we have other elements in the list other than just the head
			head->blink = nullptr; // update head's blink pointer to null, since it is a regular double-linked list and the head doesn't point backwards to the tail
		else
			tail = nullptr; // update the tail as well to be null if our list is now null
	}

	Node* curr = head; // variable used in traversal
	while (curr != nullptr && curr->value != value)
		curr = curr->flink;

	if (curr == nullptr) // if no element was found, exit
		return;

	if (curr == tail) { // if the tail is to be removed
		tail = tail->blink; // move tail to previous element
		tail->flink = nullptr; // update new tail's flink to be nullptr
		delete curr; // cleanup
		return;
	}

	// else, if the node is in the middle, update it
	curr->blink->flink = curr->flink; // update the previous node's flink pointer to point to the next element of the one to be deleted
	curr->flink->blink = curr->blink; // update the next node's blink pointer to point to the previous element of the one to be deleted
	delete curr; // cleanup
}
*/

void cleanupLinkedList(Node*& head, Node*& tail) {
	// here they are passed as references since we want to null them out and we need the actual pointers for that
	Node* curr = head; // start forward from the head; works either way, starting forwards from the head or starting backwards from the tail
	do {
		Node* aux = curr; // save the current pointer in an auxiliary variable
		curr = curr->flink; // move to the next element
		delete aux; // delete the previous one (the one we saved in the auxiliary variable)
	} while (curr != head);

	head = tail = nullptr; // make both the head and tail be null pointers
}

int main() {
	cout << "Tasks:" << endl;
	cout << "1. Create a frequency vector for vowels per word from a sentence (words delimited by spaces)" << endl;
	cout << "2. Implement a double-linked list (addition of elements and traversal)" << endl;

	int option;
	cout << "Enter task to solve (or 3 to exit): ";
	cin >> option;

	while (true) {
		switch (option) {
			case 1: {
				unsigned int size; // declare variables
				cout << "Enter the maximum size of the sentence: ";
				cin >> size;

				if (size < 1) { // ensure good size
					cout << "Invalid size! Try again." << endl;
					break;
				}
				
				char* sentence = new char[size]; // declare and read sentence
				cout << "Enter sentence: ";
				cin.ignore();
				cin.getline(sentence, size);

				int noWords = countWords(sentence); // obtain number of words to know the amount of rows our frequency map has
				int** frequencyMap = countVowelsPerWord(sentence);
				
				const char* vowels = "aeiouAEIOU"; // string for vowels, used in printing

				for (int i = 0; i < noWords; i++) {
					cout << "For word " << i + 1 << " we have the following frequencies for vowels" << endl;
					for (int j = 0; j < 10; j++)
						cout << vowels[j] << ":" << frequencyMap[i][j] << " ";
					cout << endl;
				}
				
				for (int i = 0; i < noWords; i++) // cleanup for the obtained pointer
					delete[] frequencyMap[i];

				delete[] frequencyMap;
				frequencyMap = nullptr;

				// cleanup for our allocated memory
				delete[] sentence;
				sentence = nullptr;
				break;
			}
			case 2: {
				void (*traversalFunction)(Node*); // declare function pointer for choosing the traversal (either forward or backward)
				// since its not dynamic memory allocated via "new" and just a variable to hold the address of a function, it needs not be cleaned up

				unsigned int size; // declare and read size
				cout << "Enter the size of the list: ";
				cin >> size;

				if (size < 1) { // ensure correct size
					cout << "Invalid size! Try again." << endl;
					break;
				}

				int* values = new int[size]; // declare array for values and read them
				cout << "Enter the values: ";
				for (int i = 0; i < size; i++)
					cin >> values[i];

				Node* head = nullptr; // declare our double-linked list
				Node* tail = nullptr;

				for (int i = 0; i < size; i++) {
					cout << "For node " << i + 1 << " choose:" << endl;
					cout << "1. Add it at the head" << endl;
					cout << "2. Add it at the tail" << endl;

					int opt;
					cout << "Option: ";
					cin >> opt;

					if (opt == 1) // check how the user wants to add the node
						addNode(head, tail, values[i], false);
					else if (opt == 2)
						addNode(head, tail, values[i], true);
					else
					{
						cout << "Invalid option! Try again." << endl;
						goto CLEANUP; // jump to cleanup if option was incorrect
					}
				}

				cout << "Choose how you want to traverse the list: " << endl;
				cout << "1. Traverse forward" << endl;
				cout << "2. Traverse backward" << endl;

				int opt;
				cout << "Option: "; // check how the user wants to traverse the linked list
				cin >> opt;

				if (opt == 1)
					traversalFunction = traverseForward; // assign function pointer to appropriate function
				else if (opt == 2)
					traversalFunction = traverseBackward;
				else {
					cout << "Invalid option! Try again." << endl;
					goto CLEANUP;
				}
				
				cout << "The desired traversal is: ";
				traversalFunction(opt == 1 ? head : tail); // not the best way to use function pointers, but still showcases how they can be used
				cout << endl;

			CLEANUP:
				delete[] values; // cleanup for our allocated dynamic memory
				values == nullptr;

				cleanupLinkedList(head, tail); // cleanup for our linked list
				break;
			}
			case 3:
				cout << "Goodbye.";
				return 0;
			default:
				cout << "Invalid option! Try again." << endl;
				break;
		}
		cout << "Enter task to solve (or 3 to exit): ";
		cin >> option;
	}
	return 0;
}