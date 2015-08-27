all: sDeque

sDeque: sDeque.cpp sDeque_main.cpp
	g++ -o sDeque sDeque_main.cpp sDeque.cpp

sDeque.o: sDeque.cpp sDeque.h
	g++ -Wall -c sDeque.cpp

sDeque_main.o: sDeque_main.cpp sDeque.h
	g++ -Wall -c sDeque_main.cpp

clean:
	rm -rf *o sDeque