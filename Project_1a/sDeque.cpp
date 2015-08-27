#include "sDeque.h"
#include <iostream>

using namespace std;

Deque::Deque()
{
    queue = new std::string[8]; // minimum size of the queue
    num_elements = 0; // empty queue
    size_of_queue = 8; // minimum size of eight (will be doubled when full and shrunk when less than 1/4 full
    front = -1; // default for empty queue
    back = -1; // default for empty queue
}
//Destructor
Deque::~Deque()
{
    delete [] queue;
}
//Inserts the element at the front of the queue
void Deque::push_front(std::string item)
{
    if(((front - 1 + size_of_queue) % size_of_queue) == back)
    {
        doubleSize();
        front = (front - 1 + size_of_queue) % size_of_queue;
    }

    else if(empty())
    {
        front = 0;
        back = 0;
    }

    else
    {
        front = (front - 1 + size_of_queue) % size_of_queue;
    }
    queue[front] = item;
    num_elements++;
}
//Inserts the element at the back of the queue
void Deque::push_back(std::string item)
{
    if(isFull())
    {
        doubleSize();
        back = (back + 1) % size_of_queue;
    }
    else if(empty())
    {
        front = 0;
        back = 0;
    }
    else
    {
        back = (back + 1) % size_of_queue;
    }
    queue[back] = item;
    num_elements++;
}
//Deletes the element at the front of the queue
std::string Deque::pop_front()
{
    std::string old = "";
    if(empty())
    {
        return "Nothing to delete.";
    }

    else if(front == back)
    {
        old = queue[front];
        front = -1;
        back = -1;
    }
    else
    {
        old = queue[front];
        front = (front + 1) % size_of_queue;
    }

    num_elements--;

    if(num_elements < (size_of_queue/4) && (size_of_queue > 8))
    {
        halfSize();
    }
    return old;
}
//Deletes the element at the back of the queue
std::string Deque::pop_back()
{
    string old = "";
    if(empty())
    {
        return "Nothing to delete.";
    }
    else if(front == back)
    {
        old = queue[back];
        front = -1;
        back = -1;
    }
    else
    {
        old = queue[back];
        back = (back - 1 + size_of_queue) % size_of_queue;
    }

    num_elements--;

    if(num_elements < (size_of_queue/4) && (size_of_queue > 8))
    {
        halfSize();
    }
    return old;
}
//Returns the number of elements in the queue
int Deque::size()
{
    return num_elements;
}
//Tells whether the queue is empty or not
bool Deque::empty()
{
    return front == -1 && back == -1;
}
/* Prints the contents of the queue from front to back
* to stdout with one string per line followed by a blank line */
std::string Deque::toStr()
{
    std::string s = "";
    if(back < front)
    {
        for(int i = front; i < size_of_queue; i++)
        {
            s = s + queue[i] + "\n";
        }
        for(int i = 0; i < back + 1; i++)
        {
            s = s + queue[i] + "\n";
        }
    }
    else if(front < back || (front == 0 && back == 0))
    {
        for(int i = front; i < back + 1; i++)
        {
            s = s + queue[i] + "\n";
        }
    }
    else if(empty())
    {
        return s;
    }
    return s;
}

bool Deque::isFull()
{
    return ((back+1) % size_of_queue) == front;
}

void Deque::doubleSize()
{
    std::string* bigger_queue = new std::string[size_of_queue*2];
    int temp = 0;
        if(front < back)
        {
            for(int i = 0, j = front; i < size_of_queue && j < back + 1; i++, j++)
            {
                bigger_queue[i] = queue[j];
            }
        }
        else
        {
            for(int i = 0, j = front; i < size_of_queue && j < size_of_queue; i++, j++)
            {
                bigger_queue[i] = queue[j];
                temp = i;
            }
            for(int i = temp + 1, j = 0; i < size_of_queue && j < back + 1; i++, j++)
            {
                bigger_queue[i] = queue[j];
            }
        }
        delete [] queue;
        queue = bigger_queue;
        size_of_queue *= 2;
        front = 0;
        back = num_elements - 1;
}

void Deque::halfSize()
{

    std::string* smaller_queue = new std::string[size_of_queue/2];
    int temp = 0;

    if(front < back)
    {
        for(int i = 0, j = front; i < size_of_queue/4 && j < back + 1; i++, j++)
        {
            smaller_queue[i] = queue[j];
        }
    }
    else
    {
        for(int i = 0, j = front; i < size_of_queue/4 && j < size_of_queue; i++, j++)
        {
            smaller_queue[i] = queue[j];
            temp = i;
        }
        for(int i = temp + 1, j = 0; i < size_of_queue/4 && j < back + 1; i++, j++)
        {
            smaller_queue[i] = queue[j];
        }
    }
        delete [] queue;
        queue = smaller_queue;
        size_of_queue /= 2;
        front = 0;
        back = num_elements - 1;
}
