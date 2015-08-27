all: tDeque

tDeque: tDeque_main.cpp tDeque.h
	g++ -o tDeque tDeque_main.cpp

tDeque_main.o: tDeque_main.cpp tDeque.h
	g++ -c tDeque_main.cpp

clean:
	rm -rf *o tDeque