WQU: UnionFind.cpp main.cpp
	g++ -o main.cpp UnionFind.cpp UnionFind

UnionFind.o: UnionFind.cpp UnionFind.h
	g++ -Wall -c UnionFind.cpp

main.o: main.o UnionFind.h
	g++ -Wall -c main.cpp
