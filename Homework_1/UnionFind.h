class UnionFind
{
    //data
    int* id; // id[a] holds the parent of a
    int* tree_size; // tracks the height of each root and its children
    //methods

public:
    //Constructor
    UnionFind(int Size);

    //Destructor
    ~UnionFind();

    //Find operation
    int Find(int x);

    //Union operation
    void Union(int x, int y);

    //Connected(x,y)?
    bool Connected(int x, int y);

    //additional methods if needed
};


