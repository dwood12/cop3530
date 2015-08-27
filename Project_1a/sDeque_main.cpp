#include <iostream>
#include "sDeque.h"

using namespace std;

int main(int argc, char **argv)
{
    int op=0;
	std::string input;
	Deque *DQ = new Deque();

	while (op<5)
	{
		std::cin>> op;
		switch(op) {
		case 0:
			std::cin>>input;
			DQ->push_front(input);
			break;
		case 1:
			std::cin>>input;
			DQ->push_back(input);
			break;
		case 2:
			DQ->pop_front();
			break;
		case 3:
			DQ->pop_back();
			break;
		case 4:
			std::cout << DQ->toStr();
			break;
		}
	}
    return 0;
}
