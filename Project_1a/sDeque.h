#include <string>

class Deque
{
private:
    std::string *queue; // The array which holds the queue
    int num_elements;   // The number of elements in the queue
    int size_of_queue;   // The capacity of the queue
    int front;          // Points to the front of the queue
    int back;           // Points to the back of the queue
public:
    //Constructor
    Deque();
    //Destructor
    ~Deque();
    //Inserts the element at the front of the queue
    void push_front(std::string item);
    //Inserts the element at the back of the queue
    void push_back(std::string item);
    //Deletes the element at the front of the queue
    std::string pop_front();
     //Deletes the element at the back of the queue
    std::string pop_back();
    //Returns the number of elements in the queue
    int size();
    //Tells whether the queue is empty or not
    bool empty();

    /* Prints the contents of the queue from front to back
	 * to stdout with one string per line followed by a blank line */
	 std::string toStr();

	 // Helper function to check if the queue is full
	 bool isFull();

	 // Doubles the capacity of the queue if it is full
	 void doubleSize();

	 // Halves the capacity of the queue if it is less than 1/4 full and larger than the minimum size of 8
	 void halfSize();
};

