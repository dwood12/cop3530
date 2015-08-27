#include <sstream>
#include <iostream>
#include <stdexcept>

template <typename T>
class Deque
{
   private:
    T *queue; // The array which holds the queue
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
    void push_front(T item);
    //Inserts the element at the back of the queue
    void push_back(T item);
    //Deletes the element at the front of the queue
    T pop_front();
     //Deletes the element at the back of the queue
    T pop_back();
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

template <typename T>
Deque<T>::Deque()
{
    queue = new T[8]; // minimum size of the queue
    num_elements = 0; // empty queue
    size_of_queue = 8; // minimum size of eight (will be doubled when full and shrunk when less than 1/4 full
    front = -1; // default for empty queue
    back = -1; // default for empty queue
}
//Destructor
template <typename T>
Deque<T>::~Deque()
{
    delete [] queue; // deletes the queue object
}
//Inserts the element at the front of the queue
template <typename T>
void Deque<T>::push_front(T item)
{
    // checks if the queue is full and doubles it if it's true
    if(((front - 1 + size_of_queue) % size_of_queue) == back)
    {
        doubleSize();
        front = (front - 1 + size_of_queue) % size_of_queue;
    }

    else if(empty())
    {
        front = 0; // index front to the first queue item
        back = 0; // index back also to the first queue item
    }

    else
    {
        front = (front - 1 + size_of_queue) % size_of_queue; // if front == 0, this will handle the wrap around, otherwise it will decrement front by one
    }
    queue[front] = item; // adds the item to the queue
    num_elements++;  // increases the number of elements in the queue
}
//Inserts the element at the back of the queue
template <typename T>
void Deque<T>::push_back(T item)
{
    // checks if the queue is full
    if(isFull())
    {
        doubleSize();
        back = (back + 1) % size_of_queue; // after resizing, moves the tail forward one to push the item back
    }
    else if(empty())
    {
        front = 0; // index front to the first queue item
        back = 0; // index back to the first queue item
    }
    else
    {
        back = (back + 1) % size_of_queue; // if back is at the end, this will handle the wrap around, otherwise it will
    }
    queue[back] = item; // add item to back
    num_elements++; // increase number of elements
}
//Deletes the element at the front of the queue
template <typename T>
T Deque<T>::pop_front()
{
    T old; // variable to hold the "deleted" string item
    if(empty())
        {
            throw std::out_of_range("Error: Attempted to pop off an empty queue."); // handles if user attempts to pop off empty queue
        }

    else if(front == back)
    {
        old = queue[front];// string to return "popped" item; old = queue[front];
        front = -1; // since last item popped of queue, front and back point to nothing on the queue
        back = -1;
    }
    else
    {
        old = queue[front];
        front = (front + 1) % size_of_queue; // handles wrap around and increments front
    }

    num_elements--; // decreases number of elements

    if(num_elements < (size_of_queue/4) && (size_of_queue > 8)) // if popped element decreases size to less than 1/4 of its capacity, shrink the queue
    {
        halfSize();
    }
    return old;
}
//Deletes the element at the back of the queue
template <typename T>
T Deque<T>::pop_back()
{
    T old;// variable to hold the "deleted" string item

    if(empty())
    {
        throw std::out_of_range("Error: Attempted to pop off an empty queue."); // handles if user attempts to pop off an empty queue
    }

    else if(front == back)
    {
        old  = queue[back];
        front = -1; // since last item popped of list, front and back point to nothing on the list
        back = -1;
    }
    else
    {
        old = queue[back];
        back = (back - 1 + size_of_queue) % size_of_queue; // handles wrap around and increments front
    }

    num_elements--;

    if(num_elements < (size_of_queue/4) && (size_of_queue > 8)) // if popped element decreases size to less than 1/4 of its capacity, shrink the queue
    {
        halfSize();
    }
    return old;
}
//Returns the number of elements in the queue
template <typename T>
int Deque<T>::size()
{
    return num_elements; // returns number of elements in the queue
}
//Tells whether the queue is empty or not
template <typename T>
bool Deque<T>::empty()
{
    return front == -1 && back == -1; // returns boolean truth if queue is empty
}
/* Prints the contents of the queue from front to back
* to stdout with one string per line followed by a blank line */
template <typename T>
std::string Deque<T>::toStr()
{
    std::string s = "";
    std::stringstream ss;
    ss << s;
    if(back < front) // if front is a higher index than front, traverse the queue from the end, then from the beginning to the back
    {
        for(int i = front; i < size_of_queue; i++)
        {
            ss << queue[i] << "\n";
        }
        for(int i = 0; i < back + 1; i++)
        {
            ss << queue[i] << "\n";
        }
    }
    else if(front < back || size() == 1) //if front is less than back, just traverse
                                         // the queue from front to back. Also handles case if queue has only one item
    {
        for(int i = front; i < back + 1; i++)
        {
            ss << queue[i] << "\n";
        }
    }
    else if(empty())
    {
        s = ss.str();
        return s; // list is empty, so nothing to add to return string
    }
    s = ss.str();
    return s;
}


// helper that returns if the back has wrapped around to the front, meaning the queue is full
template <typename T>
bool Deque<T>::isFull()
{
    return ((back+1) % size_of_queue) == front; //
}

// helper function that handles doubling the queue
template <typename T>
void Deque<T>::doubleSize()
{
    try
    {
        T* bigger_queue = new T[size_of_queue*2]; // create queue with twice the capacity
        int temp = 0; // temp to store value of i when traversing the queue
        if(front < back)
        {
            for(int i = 0, j = front; i < size_of_queue && j < back + 1; i++, j++)
            {
                bigger_queue[i] = queue[j]; // finds the front in the queue and places it in the first position of the bigger queue,
                                            // then fills the rest of the items to the head (if front is less than index of back)
            }
        }
        else
        {
            for(int i = 0, j = front; i < size_of_queue && j < size_of_queue; i++, j++)
            {
                bigger_queue[i] = queue[j]; // finds the front in the queue and places it in the first position of the bigger queue
                temp = i; // up to the size of the queue, then saves value of i to continue queue traversing in next loop
            }
            for(int i = temp + 1, j = 0; i < size_of_queue && j < back + 1; i++, j++)
            {
                bigger_queue[i] = queue[j]; // continues from the item after the temp position to the back (if front is greater than back)
            }
        }
                delete [] queue; // deletes old queue
                queue = bigger_queue; // points queue pointer to the new queue
                size_of_queue *= 2; // double size variable
                front = 0; // reset front to the zero index
                back = num_elements - 1; // reset back to the value it was before resizing
    }
    catch(std::bad_alloc ba)
    {
        std::cout << "Error: Queue is too large." << std::endl; //handles the case if the queue becomes too large
        throw;
    }
}

template <typename T>
void Deque<T>::halfSize()
{
    T* smaller_queue = new T[size_of_queue/2]; // create queue with half the capacity
    int temp = 0; // temp to store value of i when traversing the queue
    if(front < back)
    {
        for(int i = 0, j = front; i < size_of_queue/4 && j < back + 1; i++, j++)
        {
            smaller_queue[i] = queue[j]; // finds the front in the queue and places it in the first position of the bigger queue,
                                        // then fills the rest of the items to the head (if front is less than index of back)
        }
    }
    else
    {
        for(int i = 0, j = front; i < size_of_queue/4 && j < size_of_queue; i++, j++)
        {
            smaller_queue[i] = queue[j]; // finds the front in the queue and places it in the first position of the bigger queue
            temp = i; // up to the size of the queue, then saves value of i to continue queue traversing in next loop
        }
        for(int i = temp + 1, j = 0; i < size_of_queue/4 && j < back + 1; i++, j++)
        {
            smaller_queue[i] = queue[j]; // continues from the item after the temp position to the back (if front is greater than back)
        }
    }
        delete [] queue; // deletes old queue
        queue = smaller_queue; // points queue pointer to the new queue
        size_of_queue /= 2; // double size variable
        front = 0; // reset front to the zero index
        back = num_elements - 1; // reset back to the value it was before resizing
}

