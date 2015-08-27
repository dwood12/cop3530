#include "UnionFind.h"

    //Constructor
    UnionFind::UnionFind(int Size)
    {
        id = new int[Size + 1];
        tree_size = new int[Size + 1];
        for(int i = 0; i < Size + 1; i++)
        {
            id[i] = i; // initialize each value as its own root
            tree_size[i] = 1; // give each value an initial size of 1
        }
    }

    //Destructor
    UnionFind::~UnionFind()
    {
        delete [] id;
        delete [] tree_size;
    }

    //Find operation
    int UnionFind::Find(int x)
    {
        while(x != id[x])
        {
            x = id[x]; // if we have not reached the root of a, check id[id[...id[a]] until root is found and return it
        }
        return x;
    }

    //Union operation
    void UnionFind::Union(int x, int y)
    {
        int root_x = Find(x); // root of x
        int root_y = Find(y); // root of y
        if(tree_size[root_x] < tree_size[root_y]) // check if weight x < weight of y
        {
            id[root_x] = root_y; // make the root of x point to root y
            tree_size[root_y] += tree_size[root_x]; // update tree size
        }
        else
        {
            id[root_y] = root_x; // make the root of y point to root x
            tree_size[root_x] += tree_size[root_y]; // update tree size
        }
    }

    //Connected(x,y)?
    bool UnionFind::Connected(int x, int y)
    {
        return Find(x) == Find(y); //find if x and y have the same value and return the boolean truth value
    }

    //additional methods if needed
