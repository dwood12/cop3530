all: bTree

bTree:  bTree_main.cpp bTree.h
	g++ -o bTree bTree_main.cpp

bTree_main.o : bTree_main.cpp bTree.h
	g++ -c bTree_main.cpp

clean:
	rm -rf *o bTree
