#include <iostream>
#include <string> // for to_string
#include <fstream> // for ifstream
using namespace std;

void resizeArray(int*& list, int currSize, int newSize) { // pointer passed as reference as to ensure that we actually modify the pointer variable instead of a copy to it
	int* newList = new int[newSize]; // create auxiliary list

	memset(newList, 0, newSize * sizeof(int)); // set the memory of the new list to 0 - could've been done with a for, but this is faster and simpler
	// memset (pointerToMemory, valueToBeSet, sizeInBytes);

	int elementsToCopy = (currSize < newSize) ? currSize : newSize; // variable that helps in resizing, as to ensure we don't copy more values than the buffer holds (for when resizing down)
	memcpy(newList, list, elementsToCopy * sizeof(int)); // copy our current array into the new one - again, could've been done with a for but this is simpler and faster
	// memcpy (pointerToDest, pointerToSource, sizeInBytes);

	delete[] list; // cleanup for our pointer
	list = newList; // assign new pointer to our initial one
}

struct Point2D { // define a structure for a point in a 2D plane
	int x, y;
	Point2D() : x(-1), y(-1) {} // default constructor, needed to be able to allocate a dynamic array (as we're using a custom type, it requires a parameter-less constructor)
	// a constructor is a special function which dictates how to create an element of this type; it is called when we're doing stuff like Point2D pt = Point2D();
	// we could have written it as Point2D() {x = -1; y = -1;}, but this approach works as well and is shorter
	Point2D(int x, int y) : x(x), y(y) {} // constructor with parameters, for when doing "Point2D pt = Point2D(5, 7)" for e.g.
}; 

Point2D getClosestPoint(int** distanceVect, bool** visited, int rows, int cols) {
	int minDist = numeric_limits<int>::max(); // initialize minimum distance with a big value (max of "int")
	Point2D minPoint = Point2D(-1, -1); // initialize minimum point with an unreachable value

	// traverse the distance vector matrix and visited matrix and find the closest point
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			if (!visited[i][j] && distanceVect[i][j] < minDist) {
				minDist = distanceVect[i][j];
				minPoint = Point2D(i, j);
			}

	return minPoint;
}

bool pathTraversalDijkstra(int** grid, int rows, int cols, Point2D source, Point2D destination, Point2D** parents) {
	const Point2D directions[4] = { Point2D(0, 1), Point2D(1, 0), Point2D(0, -1), Point2D(-1, 0) }; // define a vector for our directions (UP, RIGHT, DOWN, LEFT)
	// const keyword makes a variable's value non-modifiable

	int** distanceVect = new int* [rows]; // create matrix that will hold the distances between each point
	for (int i = 0; i < rows; i++)
		distanceVect[i] = new int[cols];

	bool** visited = new bool* [rows]; // create bool matrix that will mark the visited points
	for (int i = 0; i < rows; i++)
		visited[i] = new bool[cols];

	for (int i = 0; i < rows; i++) // initialize data
		for (int j = 0; j < cols; j++) {
			distanceVect[i][j] = numeric_limits<int>::max(); // assign each distance the max value of an "int"
			parents[i][j] = Point2D(-1, -1); // assign null parents to each node, as they weren't visited yet
			visited[i][j] = false; // all points are currently unvisited
		}

	if (grid[source.x][source.y] == 1 || grid[destination.x][destination.y] == 1) // if our source or destination are blocked by a wall jump to cleanup
		// the goto instructions jumps to a defined label\
		// labels are defined by words (no spaces, but can use other characters such as _) followed by ":", as can be seen
		goto CLEANUP;

	//visited[source.x][source.y] = true; // mark source node as visited
	distanceVect[source.x][source.y] = 0; // distance to source is 0, since we are already there

	for (int i = 0; i < rows * cols; i++) {
		// get closest point
		Point2D closest = getClosestPoint(distanceVect, visited, rows, cols);
		if (closest.x == -1 && closest.y == -1) // if we have no more unvisited/reachable points
			break;

		visited[closest.x][closest.y] = true; // mark the point as visited

		if (closest.x == destination.x && closest.y == destination.y) // check to see if we reached the destination
			break;

		for (Point2D newDir : directions) { // check all neighbors
			int possX = newDir.x + closest.x;
			int possY = newDir.y + closest.y;

			if (0 <= possX && possX < rows && 0 <= possY && possY < cols && !grid[possX][possY])  // check to see if our new calculated values are within the bounds of allocation
				// also checks if the current point is reachable (i.e. if it is not a wall); wall = 1; not wall = 0;
				if (distanceVect[closest.x][closest.y] + 1 < distanceVect[possX][possY]) { // if our new distance is smaller than what we've done until now to reach that point
					distanceVect[possX][possY] = distanceVect[closest.x][closest.y] + 1; // update the distance
					parents[possX][possY] = closest; // update the parent
				}
		}
	}
CLEANUP: // label used to identify a portion of the code
	bool ret = (distanceVect[destination.x][destination.y] != numeric_limits<int>::max()); // return value
	// determines whether we were successful in reaching the destination point

	// cleanup for our dynamically allocated arrays
	for (int i = 0; i < rows; i++)
		delete[] distanceVect[i], delete[] visited[i];

	delete[] distanceVect;
	delete[] visited;
	distanceVect = nullptr;
	visited = nullptr;

	return ret;
}

string getPath(Point2D** parents, Point2D destination) {
	// function that will build the path based on the parents matrix
	string path = ""; // string that will hold the return value, i.e. the path

	for (Point2D current = destination; current.x != -1 && current.y != -1; current = parents[current.x][current.y]) {
		// go from the last node up the parents list until we reach the source (we go from parent to parent, reconstructing the path in reverse)
		path += (")" + to_string(current.y) + " ," + to_string(current.x) + "("); // keep in mind the path is reversed, since we go from destination up to source, so we build the string in reverse and then reverse it to get the normal string
		if (parents[current.x][current.y].x != -1 && parents[current.x][current.y].y != -1) // if we haven't reached the source yet
			path += " >- ";
	}
	reverse(path.begin(), path.end()); // reverse the string
	// path.begin() returns an iterator for the string pointing at the start of the string, and path.end() returns one pointing at the end of the string, which are basically pointers to the string
	// we could use them in a for loop as such
	// for (string::iterator it = path.begin(); it != path.end(); it++) cout << *it;
	// to obtain the value at the iterator, use dereferencing
	// the iterator type's depends on type of the underlying array, if "vector<int>" were to be used, the iterator would've been declared as "vector<int>::iterator"
	// for such situations, we can also use the "auto" keywords in C++, which deduces the appropriate type of the variable depending on the type that's assigned to it
	// thus, it would make that example for loop look like this
	// for (auto it = path.begin(); it != path.end(); it++) cout << *it;
	return path;
}


struct Node {
	int data;
	Node* nextNode;

	Node(int value) : data(value), nextNode(nullptr) {}
};

void insertLinkedList(Node*& head, int value) {
	if (head == nullptr) { // if we have no values in our linked list
		head = new Node(value); // using the constructor we made to assign the value to the node
		return; // exit the function prematurely, since it is void no value is returned
	}

	Node* aux = head; // use an auxiliary node to traverse the list
	while (aux->nextNode != nullptr) // traverse the list up to the last node
		// quick note here, when using regular structs, we would access the nextNode variable as such: "aux.nextNode" (using the "." operator) (valid for member functions and in classes as well)
		// but since "aux" is a pointer to a struct, accessing its members is done via the "->" operator
		// this is valid for member functions as well, and remains valid with classes as well
		aux = aux->nextNode;

	aux->nextNode = new Node(value); // assign the next node of the last one to be our new one
}

void printLinkedList(Node* head) {
	while (head != nullptr) { // traverse the list and print its data
		cout << head->data << " ";
		head = head->nextNode; // since we didn't use a reference to our pointer, this modification doesn't affect it
	}
}

void removeNode(Node*& head, int value) {
	// function to delete a node from the linked list
	// not used in the program, but is here just to showcase how
	if (head == nullptr)
		return; // if the list is empty, we have nothing to do
	if (head->data == value) {
		// if the value to be deleted is in the head
		Node* aux = head; // store our current head in an auxiliary variable
		head = head->nextNode; // make the next element be the head
		delete aux; // cleanup
		return;
	}

	Node* aux = head; // auxiliary variable to traverse the list
	while (aux->nextNode != nullptr && aux->nextNode->data != value)
		aux = aux->nextNode;

	if (aux->nextNode == nullptr) // if the value wasn't found exit
		return;

	Node* deletedNode = aux->nextNode;
	aux->nextNode = aux->nextNode->nextNode;
	delete deletedNode;
}

void deleteLinkedList(Node*& head) {
	// function for cleaning up the memory used by the linked list
	Node* curr = head; // copy of the head pointer
	Node* next = nullptr;

	while (curr != nullptr) {
		next = curr->nextNode; // save next node
		delete curr; // delete current one
		curr = next; // move to the next one
	}

	head = nullptr; // set the head as null, since it's been already deleted
}

int main() {
	cout << "Tasks:" << endl;
	cout << "1. Resize a dynamic array" << endl;
	cout << "2. Path traversal algorithm for a dynamic 2D array (Dijkstra's algorithm)" << endl;
	cout << "3. Linked-list (insertion and traversal)" << endl;

	int option;
	cout << "Enter the task to solve (or 4 to exit): ";
	cin >> option;
	while (true) {
		switch (option) {
			case 1: {
				unsigned int currSize, newSize; // declare variables - making them unsigned such that the user cannot insert negative values
				cout << "Enter initial size: ";
				cin >> currSize;
				if (currSize < 1) {
					cout << "Invalid size! Try again." << endl;
					break;
				}

				int* list = new int[currSize]; // initialize memory for the dynamic array
				cout << "Enter array elements: ";
				for (int i = 0; i < currSize; i++)
					cin >> list[i]; // read elements into array

				cout << "Enter new size: "; // read new size
				cin >> newSize;
				if (newSize < 1) {
					cout << "Invalid size! Try again." << endl;
					break;
				}

				resizeArray(list, currSize, newSize);

				cout << "Resized array is: " << endl;
				for (int i = 0; i < newSize; i++) // print resized array
					cout << list[i] << " ";

				cout << endl;
				delete[] list; // cleanup for dynamic array
				list = nullptr;
				break;
			}
			case 2: {
				cout << "2.1. Enter data from keyboard" << endl;
				cout << "2.2. Enter data from file" << endl;

				int opt;
				cout << "Enter option: ";
				cin >> opt;

				if (opt == 1) {
					unsigned int rows, cols; // making them unsigned such that the user cannot insert negative values
					cout << "Enter number of rows: ";
					cin >> rows;
					cout << "Enter number of columns: ";
					cin >> cols;

					unsigned int noWalls;
					cout << "Enter number of walls: ";
					cin >> noWalls;
					if (noWalls >= rows * cols ) {
						cout << "Cannot insert more walls than the amount of points in order to have a chance for a good path. Setting it to half." << endl;
						noWalls = rows * cols / 2;
					}

					int** grid = new int* [rows]; // declare grid
					for (int i = 0; i < rows; i++) {
						grid[i] = new int[cols];
						memset(grid[i], 0, cols * sizeof(int)); // set all values to 0
					}

					for (int i = 0; i < noWalls; i++) { // set walls to 1
						cout << "Wall " << i + 1 << ": " << endl;
						unsigned int x, y;
						cout << "x=";
						cin >> x;
						cout << "y=";
						cin >> y;
						if (x >= rows || y >= cols) // ensure we are within the bounds
							cout << "Invalid wall coordinate. Skipping it..." << endl;
						else
							grid[x][y] = 1;
					}

					// print the grid
					cout << "Grid is: " << endl;
					for (int i = 0; i < rows; i++) {
						for (int j = 0; j < cols; j++)
							cout << grid[i][j] << " ";
						cout << endl;
					}

					Point2D** parents = new Point2D*[rows]; // declare and initalize parents matrix
					for (int i = 0; i < rows; i++)
						parents[i] = new Point2D[cols];

					int srcX, srcY, destX, destY;

					cout << "Source X=";
					cin >> srcX;
					cout << "Source Y=";
					cin >> srcY;
					if (srcX >= rows || srcY >= cols) {
						cout << "Invalid source location, setting it to (0, 0)." << endl;
						srcX = srcY = 0; // it first makes srcY = 0, then does srcX = srcY
					}
						
					cout << "Destination X=";
					cin >> destX;
					cout << "Destination Y=";
					cin >> destY;
					if (destX >= rows || destY >= cols) {
						cout << "Invalid destination location, setting it to (rows - 1, cols - 1)." << endl;
						destX = rows - 1;
						destY = cols - 1;
					}

					if (pathTraversalDijkstra(grid, rows, cols, Point2D(srcX, srcY), Point2D(destX, destY), parents))
						cout << "Path is: " << getPath(parents, Point2D(destX, destY)) << endl;
					else
						cout << "No path found." << endl;

					// cleanup for our dynamic arrays
					for (int i = 0; i < rows; i++)
						delete[] grid[i], delete[] parents[i]; // "," operator allows you to do multiple instructions 

					delete[] grid;
					delete[] parents;
					grid = nullptr;
					parents = nullptr;
				}
				else if (opt == 2) {
					// print filename format
					cout << "Filename has to have the following format:" << endl;
					cout << "numberOfRows numberOfColumns" << endl;
					cout << "sourceX sourceY" << endl;
					cout << "destinationX destinationY" << endl;
					cout << "numberOfWalls" << endl;
					cout << "For the following \"numberOfWalls\" lines, insert " << endl;
					cout << "wallX wallY" << endl;

					string FILENAME;
					cout << "Enter filename (absolute path): ";
					cin.ignore();
					getline(cin, FILENAME);
					//cin >> FILENAME; // read filename

					ifstream f(FILENAME); // open read stream to file; ifstream = input file stream
					// for output, we have ofstream = output file stream
					// to write to it we use the "<<" operator, as with cout (console output stream)

					if (!f.is_open()) // check if we opened the file successfully
						cout << "Invalid filename or error when opening. Please try again." << endl;
					else {
						unsigned int rows, cols, srcX, srcY, destX, destY, noWalls;
						// read from a file stream as you'd usually do with stringstreams/cin (console input stream)
						// works to read multiple data types, but if we had strings with spaces, we had to use getline(f, line);
						f >> rows >> cols;
						cout << "rows=" << rows << " and columns=" << cols << endl;

						f >> srcX >> srcY;
						if (srcX >= rows || srcY >= cols) {
							cout << "Invalid source location, setting it to (0, 0)." << endl;
							srcX = srcY = 0;
						}
						cout << "sourceX=" << srcX << " and sourceY=" << srcY << endl;

						f >> destX >> destY;
						if (destX >= rows || destY >= cols) {
							cout << "Invalid destination location, setting it to (rows - 1, cols - 1)." << endl;
							destX = rows - 1;
							destY = cols - 1;
						}
						cout << "destionationX=" << destX << " and destinationY=" << destY << endl;

						f >> noWalls;
						if (noWalls >= rows * cols) {
							cout << "Cannot insert more walls than the amount of points in order to have a chance for a good path. Setting it to half." << endl;
							noWalls = rows * cols / 2;
						}
						cout << "noWalls=" << noWalls << endl;
						
						// follow same algorithm as before
						int** grid = new int* [rows]; // declare grid
						for (int i = 0; i < rows; i++) {
							grid[i] = new int[cols];
							memset(grid[i], 0, cols * sizeof(int)); // set all values to 0
						}

						for (int i = 0; i < noWalls; i++) { // set walls to 1
							unsigned int x, y;
							f >> x >> y;
							
							if (x >= rows || y >= cols)
								cout << "Invalid wall coordinate. Skipping it..." << endl;
							else {
								cout << "Wall " << i + 1 << " x=" << x << ", y=" << y << endl;
								grid[x][y] = 1;
							}
						}
						f.close(); // close filestream after we're done reading

						// print the grid
						cout << "Grid is: " << endl;
						for (int i = 0; i < rows; i++) {
							for (int j = 0; j < cols; j++)
								cout << grid[i][j] << " ";
							cout << endl;
						}

						Point2D** parents = new Point2D * [rows];
						for (int i = 0; i < rows; i++)
							parents[i] = new Point2D[cols];

						if (pathTraversalDijkstra(grid, rows, cols, Point2D(srcX, srcY), Point2D(destX, destY), parents))
							cout << "Path is: " << getPath(parents, Point2D(destX, destY)) << endl;
						else
							cout << "No path found." << endl;

						// cleanup for our dynamic arrays
						for (int i = 0; i < rows; i++)
							delete[] grid[i], delete[] parents[i]; 

						delete[] grid;
						delete[] parents;
						grid = nullptr;
						parents = nullptr;
					}
				}
				else
					cout << "Invalid option! Try again.";
				
				break;
			}
			case 3: {
				unsigned int size; // declare variables
				cout << "Enter the size of the linked list: ";
				cin >> size; // read size
				if (size < 1) {
					cout << "Invalid size! Try again." << endl;
					break;
				}

				int* values = new int[size]; // declare an array to hold the values of the list
				cout << "Enter elements: ";
				for (int i = 0; i < size; i++) // read a list of the elements
					cin >> values[i];

				Node* head = nullptr; // initialize our head to an empty pointer

				for (int i = 0; i < size; i++)
					insertLinkedList(head, values[i]); // insert our values into the linked list

				cout << "The list's values are: " << endl; // print the values
				printLinkedList(head);
				cout << endl;

				delete[] values; // cleanup for our dynamic array
				values = nullptr;

				deleteLinkedList(head); // call cleanup for the linked list
				break;
			}
			case 4: 
				cout << "Goodbye!";
				return 0;
			default:
				cout << "Invalid option! Try again." << endl;
				break;
		}
		cout << "Enter the task to solve (or 4 to exit): ";
		cin >> option;
	}
	return 0;
}
