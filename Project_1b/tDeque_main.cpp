#include"tDeque.h"
using namespace std;

template <typename T>
void test (T s) {
	Deque<T> *DQ = new Deque<T>();
	T input;
	int op=0;

	while (op<7)
	{
		std::cin>> op;
		switch(op) {
		case 0:
			std::cin>>input;
			try {
				DQ->push_front(input);
			} catch (exception e) {
				cout<<"Out of Memory Exception!"<<endl;
			}
			break;
		case 1:
			std::cin>>input;
			try{
				DQ->push_back(input);
			} catch (exception e) {
				cout<<"Out of Memory Exception!"<<endl;
			}
			break;
		case 2:
			try{
				std::cout<<DQ->pop_front()<<std::endl;
			} catch (exception e) {
				cout<<"Caught Exception for empty stack!"<<endl;
			}
			break;
		case 3:
		try{
				std::cout<<DQ->pop_back()<<std::endl;
			} catch (exception e) {
				cout<<"Caught Exception for empty stack!"<<endl;
			}
			break;
		case 4:
			std::cout<<DQ->toStr();
			break;
		case 5:
			std::cout<<DQ->size()<<std::endl;
			break;
		case 6:
			std::cout<<DQ->empty()<<std::endl;
			break;
		}
	}
}


int main(int argc, char **argv) {
	int op=0;
	std::string input;
	int type;
	cin>>type;
	string s = "tDeque";
	switch(type) {
		case 0:
			test(s);
			break;
		case 1:
			test(3.2);
			break;
		case 2:
			test(1);
			break;
		default:
			return 1;
	}

	return 0;

}
