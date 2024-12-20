#include <iostream>
#include <fstream>
#include <string>

// define custom exceptions, without inheritance
class HeapEmptyException {
	private:
		const char* msg;
	public:
		HeapEmptyException(const char* msg) : msg(msg) {}
		const char* what() const { return this->msg; }
};

class HeapFullException {
	private:
		const char* msg;
	public:
		HeapFullException(const char* msg) : msg(msg) {}
		const char* what() const { return this->msg; }
};

class HeapInvalidException {
	private:
		const char* msg;
	public:
		HeapInvalidException(const char* msg) : msg(msg) {}
		const char* what() const { return this->msg; }
};

struct Node { // heap node, it is a binary tree, hence it will have a left and right, and also a parent so we can keep track of them
	int value;
	Node *parent, *left, *right;

	Node() : value(0), parent(nullptr), left(nullptr), right(nullptr) {}
	Node(int value) : value(value), parent(nullptr), left(nullptr), right(nullptr) {}
};


// the tree will look like this
//               *
//              / \
//             /   \
//            *     *
//           / \   / \
//          *   * *   *
//        ..............

struct QueueNode { // define an element of the queue (basically a simple doubly-linked list)
	Node* data;
	QueueNode* next;
	QueueNode(Node* n) : data(n), next(nullptr) {}
};

class Queue { // custom implementation of a queue for the traversal
    private:
        QueueNode* front;
        QueueNode* rear;

    public:
        Queue() : front(nullptr), rear(nullptr) {}

        ~Queue() {
            while (!this->isEmpty()) {
                this->dequeue();
            }
        }

        void enqueue(Node* data) {
            QueueNode* newNode = new QueueNode(data);

            if (this->isEmpty()) {
                this->front = this->rear = newNode;
            }
            else {
                this->rear->next = newNode; // queue is FIFO (first-in-first-out), so the new element is added at the end
                this->rear = newNode;
            }
        }

        Node* dequeue() { // pop first element (due to FIFO)
            if (this->isEmpty())
                return nullptr;

            QueueNode* temp = this->front;
            Node* data = temp->data;
            this->front = this->front->next;

            if (this->front == nullptr) {
                this->rear = nullptr;
            }

            delete temp;
            return data;
        }

        bool isEmpty() {
            return this->front == nullptr;
        }

};

class MinHeap {
    private: // keep important internal functions private, and expose only the final variants that are to be used by the user
        Node* root;
        size_t size;
        const static size_t MAX_SIZE = 100; // define a maximum size for it

        Node* findLeafNode() { // find a leaf node
            if (!this->root) 
                return nullptr;

            Queue q;
            q.enqueue(this->root);
            Node* last = nullptr;

            while (!q.isEmpty()) {
                last = q.dequeue(); // remove element from queue

                if (last->left) 
                    q.enqueue(last->left); // add both if they exist, so we can traverse them via the dequeue operation above
                if (last->right) 
                    q.enqueue(last->right);
            }

            return last;
        }

        // traverse the heap and see where we can add an element
        Node* findInsertPosition() {
            if (!this->root) 
                return nullptr;

            Queue q;
            q.enqueue(this->root);

            while (!q.isEmpty()) {
                Node* current = q.dequeue();

                if (!current->left) // if we found an empty node, return it
                    return current;
                if (!current->right) 
                    return current;

                q.enqueue(current->left);
                q.enqueue(current->right);
            }

            return nullptr;
        }

        void heapifyUp(Node* node) { // traverse the tree up from a node and fix values by swapping incorrect nodes
            // this is done when adding/modifying a node's value as to fix the parent's subtree and ensure it is still in order
            // moves a node up the tree until the heap property is respected
            // hence, it is to be used when there are violations at the bottom of the heap
            while (node->parent && node->value < node->parent->value) {
                int temp = node->value;
                node->value = node->parent->value;
                node->parent->value = temp;
                node = node->parent;
            }
        }

        void heapifyDown(Node* node) { // traverse the heap down and arrange values accordingly
            // this is done when removing, so we can fix the entire subtree upon removal,
            // since removal requires replacing a value with the last element, which is big in value (for a MinHeap), this moves it down the tree until the heap property is respected
            // hence, it is to be used when there are violations at the top of the heap
            while (true) {
                Node* smallest = node;
                
                // obtain the smaller node
                if (node->left && node->left->value < smallest->value)
                    smallest = node->left;

                if (node->right && node->right->value < smallest->value)
                    smallest = node->right;
                // if our node is the smallest, then we heapified correctly and are done
                if (smallest == node) 
                    break;

                int temp = node->value;
                node->value = smallest->value;
                smallest->value = temp;

                node = smallest;
            }
        }

        void deleteTree(Node* node) { // helper for the destructor
            if (node) {
                this->deleteTree(node->left);
                this->deleteTree(node->right);
                delete node;
            }
        }

        Node* findNode(Node* current, int value) { // find a node by the provided value
            if (!current) 
                return nullptr;
            if (current->value == value) 
                return current;

            Node* leftResult = this->findNode(current->left, value); // go to the left and search
            if (leftResult) 
                return leftResult;

            return this->findNode(current->right, value); // if its not to the left, then is has to be to the right, or not at all
        }

        void writeToFile(Node* node, std::ofstream& f) {
            if (!node) {
                f << -1 << " ";
                return;
            }

            f << node->value << " ";
            this->writeToFile(node->left, f); // write left subtree
            this->writeToFile(node->right, f); // write right subtree
        }

        Node* readFromFile(Node* parent, std::ifstream& i) {
            int value;
            i >> value;

            if (value == -1)
                return nullptr;

            Node* node = new Node(value);
            node->parent = parent;
            node->left = this->readFromFile(node, i); // read left subtree
            node->right = this->readFromFile(node, i); // read right subtree

            return node;
        }

        int getHeight(Node* node) { // get height of the tree starting from the given node 
            if (!node) 
                return 0;
            int leftHeight = this->getHeight(node->left);
            int rightHeight = this->getHeight(node->right);

            return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
        }

        void printSpaces(int count) { // helper for printing spaces
            for (int i = 0; i < count; i++) {
                std::cout << " ";
            }
        }

    public:
        MinHeap() : root(nullptr), size(0) {}

        ~MinHeap() {
            this->deleteTree(this->root);
        }

        void insert(int value) {
            if (this->size >= MAX_SIZE) {
                throw HeapFullException("Heap is full!");
            }

            Node* newNode = new Node(value);
            this->size++;

            if (!this->root) {
                this->root = newNode;
                return;
            }

            Node* parent = this->findInsertPosition(); // find a free position to insert
            newNode->parent = parent;

            if (!parent->left)
                parent->left = newNode;
            else
                parent->right = newNode;

            this->heapifyUp(newNode); // move the node up as necessary and ensure its placement is correct
        }

        void deleteNode(int value) {
            if (!this->root) {
                throw HeapEmptyException("Heap is empty!");
            }

            Node* nodeToDelete = this->findNode(this->root, value);
            if (!nodeToDelete) {
                throw HeapInvalidException("Given node doesn't exist!");
            }

            if (this->size == 1) { // treat root case
                delete this->root;
                this->root = nullptr;
                this->size = 0;
                return;
            }

            Node* lastNode = this->findLeafNode();

            // treat leaf case
            if (nodeToDelete == lastNode) {
                if (lastNode->parent->right == lastNode)
                    lastNode->parent->right = nullptr;
                else
                    lastNode->parent->left = nullptr;
                delete lastNode;
                this->size--;
                return;
            }

            // apply same logic as with the root deletion
            nodeToDelete->value = lastNode->value;
            if (lastNode->parent->right == lastNode)
                lastNode->parent->right = nullptr;
            else
                lastNode->parent->left = nullptr;

            delete lastNode;
            this->size--;

            // we need both since the heap may not be properly fixed just by one, as we don't know what that value was and where it was in the heap
            this->heapifyDown(nodeToDelete);
            this->heapifyUp(nodeToDelete);
        }

        int getRoot() {
            if (!this->root) {
                throw HeapEmptyException("Heap is empty!");
            }
            return this->root->value;
        }

        int removeRoot() {
            if (!this->root) {
                throw HeapEmptyException("Heap is empty!");
            }

            int rootValue = this->root->value;

            if (this->size == 1) {
                delete this->root;
                this->root = nullptr;
                this->size = 0;
                return rootValue;
            }

            Node* lastNode = this->findLeafNode(); // find leaf
            this->root->value = lastNode->value; // assign the root value to it
            // update sides of parent of our leaf node
            if (lastNode->parent->right == lastNode)
                lastNode->parent->right = nullptr;
            else
                lastNode->parent->left = nullptr;

            delete lastNode; // delete it, since we moved it to the root and fixed his parents
            this->size--;

            if (this->root)
                this->heapifyDown(this->root); // update the tree down from the root (which has now the leaf's value)

            return rootValue;
        }

        void decreaseValue(int oldValue, int amount) {
            Node* node = this->findNode(this->root, oldValue);
            if (!node) {
                throw HeapInvalidException("Node could not be found!");
            }

            node->value -= amount;
            this->heapifyUp(node); // fix heap on the side of the modified node
        }

        void print() {
            if (!this->root) {
                throw HeapEmptyException("Heap is empty!");
            }

            int height = getHeight(this->root);
            int maxNodes = (1 << height) - 1; // 2^height - 1 - the number of nodes in a complete binary search tree
            int width = maxNodes * 4; // ensure enough spaces for all nodes - obtained from testing

            Queue currentLevelQueue;
            currentLevelQueue.enqueue(this->root);

            for (int level = 0; level < height; level++) {
                int nodeCount = 1 << level;
                int gap = width / nodeCount; // reduce width with each level

                this->printSpaces(gap / 2);

                Queue nextLevelQueue;
                for (int i = 0; i < nodeCount; i++) {
                    Node* current = currentLevelQueue.dequeue();
                    if (current) {
                        std::cout << current->value;
                        nextLevelQueue.enqueue(current->left);
                        nextLevelQueue.enqueue(current->right);
                    }
                    else { // account for leafs/empty children
                        std::cout << " ";
                        nextLevelQueue.enqueue(nullptr);
                        nextLevelQueue.enqueue(nullptr);
                    }

                    this->printSpaces(gap - 1);
                }
                std::cout << std::endl << std::endl;

                // advance to the next level
                while (!nextLevelQueue.isEmpty()) {
                    currentLevelQueue.enqueue(nextLevelQueue.dequeue());
                }
            }

            std::cout << std::endl << std::endl; // add separation
        }


        void saveToFile(const char* filename) {
            std::ofstream f(filename);
            if (!f.is_open()) {
                throw HeapInvalidException("Cannot open file for writing");
            }

            f << this->size << '\n'; // add size first
            this->writeToFile(this->root, f);

            f.close();
        }

        void loadFromFile(const char* filename) {
            std::ifstream i(filename);
            if (!i.is_open()) {
                throw HeapInvalidException("Cannot open file for reading");
            }

            // clear existing tree if there is any
            this->deleteTree(this->root);
            this->root = nullptr;

            i >> this->size;
            this->root = this->readFromFile(nullptr, i); // since the root's parent is null

            i.close();
        }

        bool isEmpty() {
            return this->root == nullptr;
        }

        size_t getSize() {
            return this->size;
        }
};

int main() {
    try {
        MinHeap heap;
        // ideally a heap is a complete binary search tree, thus it has 2^n - 1 elements
        heap.insert(5);
        heap.insert(3);
        heap.insert(7);
        heap.insert(1);
        heap.insert(4);
        heap.insert(6);
        heap.insert(2);

        std::cout << "Original heap: " << std::endl;
        heap.print();
        heap.saveToFile("heap.txt");

        MinHeap loadedHeap;
        loadedHeap.loadFromFile("heap.txt");
        
        std::cout << "Loaded heap: " << std::endl;
        loadedHeap.print();

        std::cout << "Decreased value: " << std::endl;
        loadedHeap.decreaseValue(7, 2);
        loadedHeap.print();

        std::cout << "Root removal: " << std::endl;
        loadedHeap.removeRoot();
        loadedHeap.print();

        std::cout << "Node deletion: " << std::endl;
        loadedHeap.deleteNode(3);
        loadedHeap.print();

        std::cout << "Making it complete BST: " << std::endl;
        loadedHeap.insert(11);
        loadedHeap.insert(8);
        loadedHeap.print();

    }
    catch (const HeapEmptyException& e) { // catch our exceptions first
        std::cout << "HeapEmptyException: " << e.what() << std::endl;
        return 1;
    }
    catch (const HeapFullException& e) {
        std::cout << "HeapFullException: " << e.what() << std::endl;
        return 1;
    }
    catch (const HeapInvalidException& e) {
        std::cout << "HeapInvalidException: " << e.what() << std::endl;
        return 1;
    }
    catch (...) { // catch any other exceptions
        std::cout << "Other exception occured!" << std::endl;
        return 1;
    }

    return 0;
}