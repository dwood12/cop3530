#include <string>
#include <sstream>
using namespace std;

static stringstream ss; // global variable for toStr() function in bTree

struct Keys // struct that holds contents of each node (keys,values)
{
    string key;
    string value;
};

class bTreeNode
{
public:
    Keys* keys; // array of all the content for each node in the tree
    int degree;
    bTreeNode** child_p; // array of pointers to each child
    int num_of_keys; // number of keys for this node
    bool leaf_n; // determines if the current node is a leaf

    bTreeNode(int _degree, bool _leaf_n); // Constructor
    void split(int index,bTreeNode* child); // split child y of the node being called, where i is the index y in the child array (called when child is full)
    void vacantInsert(string key, string value); // insert new key into subtree within the node (non-full node)
    void goOverTree(); // looks through all nodes in subtree of node
    bool find(string key, string* value); //  called by bTree to search nodes for key, and if found return true and set value called from main, else return false
    bTreeNode* search(string key, string* value); // helper function called by searching for a key in the subtree within the note and returns null if the key is not there
    void delete_key(string key);

    //delete helper functions
    int getKey(string key); // returns index of first key >= to paramter key
    void removeLeaf(int index); // removes key present in index position of this leaf node
    void removeMidNode(int index); // removes key present in index position of this non-leaf node
    string predecessor(int index); // finds the predecessor of the key in this index of this node
    string successor(int index); // finds the successor of the key in this index of this node
    void fillIn(int index); // fills up the child node in this index position of the child array  of this node
    void retrieveFromPrev(int index); // borrows a key from the (index - 1) node and places in this index position of the child array
    void retrieveFromNext(int index); //  borrows a key from the (index + 1) node and places in this index position of the child array
    void join(int index); // merges child of this index from the node with the child of the (index + 1) node

    // bTree made a friend so that it can access private members of this class within bTree functions
    friend class bTree;
};

class bTree
{
private:
    int degree; // degree of bTree
    bTreeNode *root; // pointer to the root node

public:
    bTree(int size); // //Constructor
    ~bTree(); //Destructor
    void insert(string key, string value);  //Inserts the value pair into the tree
    bool find(string key, string* value);  // Searches for the key in the tree, if found, it returns true else returns false.
                                          // If the key is found, it stores the value in the *value variable
    void delete_key(string key); //Searches for the key and deletes it. Returns true if deletion was successful, returns false if the key wasn't found
    string toStr(); // concatenates the contents of the tree from an inorder traversal into an output stream with each string item followed by a newline character in the stream

    void goOverTree(); // helper function for toStr() function to traverse the tree
};

bTree::bTree(int size)
{
    root = NULL; // initializes the root to null
    degree = size; // minimum degree for the tree passed by the user
}

bTree::~bTree()
{
    delete [] root;
    root = NULL;
}

void bTree::insert(string key, string value)
{
    if(root == NULL) // checks if tree is empty
    {
        root = new bTreeNode(degree,true); // memory is allocated
        root->keys[0].key = key; // key and value inserted
        root->keys[0].value = value;
        root->num_of_keys = 1; // number of keys updated
    }
    else // tree is not empty
    {
        if(root->num_of_keys == 2*degree - 1) // if root is full, then the height of the tree must grow
        {
            bTreeNode* n_root = new bTreeNode(degree,false); // memory allocated for new root
            n_root->child_p[0] = root; // old root is child of new root
            n_root->split(0,root); // split old root and move one key to new root

            // New root contains two children, so must decide which gets new key
            int index = 0;
            if(n_root->keys[0].key < key)
                index++;
            n_root->child_p[index]->vacantInsert(key,value); // insert in non-full child
            root = n_root; // change root
        }
        else // if non-full root, insert key into root
        {
            root->vacantInsert(key,value);
        }
    }
}

void bTree::delete_key(string key)
{
        if(!root) // if tree is empty
        {
            return;
        }

        root->delete_key(key); //  call bTreeNode delete_key(key) function on root
        if(root->num_of_keys == 0) // if root node has 0 keys, make its first child the new root, and if no child, set root to null
        {
            bTreeNode *temp = root;
            if(root->leaf_n)
            {
                root = NULL;
            }
            else
            {
                root = root->child_p[0];
            }
            delete temp; // delete old root;
        }
}

bool bTree::find(string key, string* value)
{
    bool found = false;
    if(root == NULL) // if tree if empty, return false;
        return found;

    else if(root->find(key,&(*value))) // traverse tree and search for key starting from the root
       found = true;
    return found;
}

string bTree::toStr()
{
    goOverTree(); // traverse tree in-order and fill global stringstream variable ss with key from all nodes
    string s = ss.str(); // set s to the keys from all the nodes in the stringstream
    ss.str(""); // clear the string stream variable before returning
    return s;
}

void bTree::goOverTree()
{
    if(root != NULL) // if tree is not empty, begin traversing the tree starting at the root node
        root->goOverTree();
}

bTreeNode::bTreeNode(int _degree, bool _leaf_n) // bTreeNode constructor
{
    degree = _degree; // set degree and leaf
    leaf_n = _leaf_n;
    keys = new Keys[2*degree - 1]; // # of keys is 2*degree - 1 for each node
    child_p = new bTreeNode*[2*degree]; // each node has 2*degree pointers to its child nodes
    num_of_keys = 0; // initialize # of keys to 0 for new node
}

void bTreeNode::goOverTree()
{
    int i; // traverse through keys and children
    for(i = 0; i < num_of_keys; i++)
    {
        if(!leaf_n) // if node is not a leaf, then traverse subtree child_p[i] before printing key[i]
            child_p[i]->goOverTree();
        ss << keys[i].key << "\n"; // fill string stream with key
    }
    if(!leaf_n) // print subtree of last child
        child_p[i]->goOverTree();
}

void bTreeNode::vacantInsert(string key, string value)
{
    int i = num_of_keys - 1; // start at rightmost element
    if(leaf_n) // leaf node
    {
        // find location of new key to be inserted and move keys greater
        // than key being inserted one place ahead
        while(i >= 0 && keys[i].key > key)
        {
            keys[i+1] = keys[i];
            i--;
        }
        keys[i+1].key = key; // imsert key and value at new location
        keys[i+1].value = value;
        num_of_keys++;
    }
    else // if not leaf node
    {
        while(i >= 0 && keys[i].key > key) // find child that will have key
          i++;

          if(child_p[i+1]->num_of_keys == 2*degree - 1) // check if child is full
          {
              split(i+1,child_p[i+1]); // if so, split child into two nodes

              if(keys[i+1].key < key) // following split, middle key of child[i] graduates up and now the new key place is determined
                i++;
          }
          child_p[i+1]->vacantInsert(key,value); // recurse back through to find proper child node for key and value
    }
}

void bTreeNode::split(int index, bTreeNode* child)
{
    // new node nNode created to store (degree - 1) keys of child
    bTreeNode *nNode = new bTreeNode(child->degree,child->leaf_n);
    nNode->num_of_keys = degree - 1;

    for(int k = 0; k < degree-1; k++) // copy latter (degree - 1) keys of child to nNode
        nNode->keys[k] = child->keys[k+degree];

    if(!child->leaf_n) // copy degree # of children of child to nNode
    {
        for(int k = 0; k < degree; k++)
            nNode->child_p[k] = child->child_p[k+degree];
    }

    child->num_of_keys = degree - 1; // reduce # of keys in child

    for(int k = num_of_keys; k >= index+1; k--) // create space for new child of nNode by moving all node's children over
        child_p[k+1] = child_p[k];

    child_p[index+1] = nNode; // link new child to this node

    for(int k = num_of_keys-1; k >= index; k--) // create space for the key of child moving to nNode and find location by moving all keys ahead
        keys[k+1] = keys[k];

    keys[index] = child->keys[degree-1]; // copy middle key of child to this node

    num_of_keys++; // increment number of keys in this node
}

bool bTreeNode::find(string key, string* value)
{
    if(search(key,&(*value)) == NULL) // helper for bTree function find; searches tree for given key and r true if found, else false
        return false;
    else
    {
        return true;
    }
}

bTreeNode* bTreeNode::search(string key, string* value)
{
    int i = 0; // search tree until finding first key >= it
    while(i < num_of_keys && key > keys[i].key)
        i++;

    if(keys[i].key == key) // if key found, set value and return this node
    {
          *value = keys[i].value;
          return this;
    }

    if(leaf_n) // if key is not found and it's a leaf node, return null
        return NULL;

    return child_p[i]->search(key,&(*value)); // continue searching until correct child is found that may contain the key
}

int bTreeNode::getKey(string key)
{
    int index = 0;
    // traverse tree until key that is >= key searched for is found an index is returned
    while(index < num_of_keys && keys[index].key < key)
    {
        ++index;
    }
    return index;
}

void bTreeNode::delete_key(string key)
{
    int index = getKey(key);
    if(index < num_of_keys && keys[index].key == key) // key is present in this node
    {
        if(leaf_n) // if leaf, remove from the leaf
            removeLeaf(index);
        else
            removeMidNode(index); // else remove from node that is a subtree
    }
    else // key is not present in this node
    {
        if(leaf_n) // if not at this node and this node is a leaf, the key in not in the tree
            return;
        bool isKeyPresent = false; // key may be present in subtree of this node; bool indicates if it is present in sub-tree of last child of node
        if(index == num_of_keys)
            isKeyPresent = true;

        if(child_p[index]->num_of_keys < degree) // if key is in child with less than min. num of keys, fill it first
        {
            fillIn(index);
        }
        // if child merged with previous child, we should recursively go through the previous child
        if(isKeyPresent && index > num_of_keys)
            child_p[index-1]->delete_key(key);
        else // else we recursively go through the child which now has the minimum # of keys
            child_p[index]->delete_key(key);
    }
    return;
}

void bTreeNode::removeLeaf(int index)
{
    for(int i = index + 1; i < num_of_keys; ++i) // move over all keys one place back
        keys[i-1] = keys[i];
    num_of_keys--; // reduce # of keys
    return;
}

void bTreeNode::removeMidNode(int index)
{
    string key = keys[index].key;

    // if the child that comes before this key has the min. # of keys, find the predecessor
    // of this key in the subtree at this index, then replace it with the predecessor. Delete the
    // predecessor key from the child
    if(child_p[index]->num_of_keys >= degree)
    {
        string pred = predecessor(index);
        keys[index].key = pred;
        child_p[index]->delete_key(pred);
    }
    // if this child that comes before this key has less than the min. # of keys, find the key's successor
    // in the subtree child that comes after this key, then replace the key with the successor and delete the successor from
    // the child
    else if(child_p[index+1]->num_of_keys >= degree)
    {
        string succ = successor(index);
        keys[index].key = succ;
        child_p[index+1]->delete_key(succ);
    }

    else // if neither the child before or after this key have the min. number of keys, merge key and the child node
         // that comes before the key into that child so that it has (2*degree - 1) keys, then delete the key
    {
        join(index);
        child_p[index]->delete_key(key);
    }
    return;
}

string bTreeNode::predecessor(int index)
{
    bTreeNode* temp = child_p[index];
    while(!temp->leaf_n) // move right until a leaf if reached
        temp = temp->child_p[temp->num_of_keys];

    return temp->keys[temp->num_of_keys-1].key; // return last key of leaf
}

string bTreeNode::successor(int index)
{
    bTreeNode* temp = child_p[index+1];
    while(!temp->leaf_n) // move left until a leaf is reached
    {
        temp = temp->child_p[0];
    }
    return temp->keys[0].key; // return first key of leaf
}

void bTreeNode::fillIn(int index)
{
    if(index != 0 && child_p[index-1]->num_of_keys >= degree) // if previous child has more than minimum number of keys, borrow key from it
        retrieveFromPrev(index);

    else if(index != num_of_keys && child_p[index + 1]->num_of_keys >= degree) // if next child has more than the minimum number of keys, borrow key from it
        retrieveFromNext(index);

    else // merge child at this index with its sibling: if its the last child, merge it with its previous sibling, else next sibling
    {
        if(index != num_of_keys)
            join(index);
        else
            join(index - 1);
    }
    return;
}

void bTreeNode::retrieveFromPrev(int index)
{
    bTreeNode *child = child_p[index];
    bTreeNode *sib = child_p[index-1];

    // Last key of sibling goes up to parent, then parent gives key in first spot of child

    // Move all keys in child ahead one
    for(int i = child->num_of_keys-1; i >= 0; --i)
        child->keys[i+1] = child->keys[i];

    // if this child is not a leaf, move its child pointers ahead too
    if(!child->leaf_n)
    {
        for(int i = child->num_of_keys; i >= 0; --i)
            child->child_p[i+1] = child->child_p[i];
    }
    // set child's first key to the (index - 1) key of the current node
    child->keys[0] = keys[index-1];

    if(!leaf_n) // moves sibling's last child as this child's first child
        child->child_p[0] = sib->child_p[sib->num_of_keys];

    keys[index - 1] = sib->keys[sib->num_of_keys-1]; // move key from sibling to parent

    child->num_of_keys = child->num_of_keys + 1; // uncrement the # of keys in the child
    sib->num_of_keys = sib->num_of_keys - 1; // decrement the # of keys in the sibling

    return;
}

void bTreeNode::retrieveFromNext(int index)
{
    bTreeNode *child = child_p[index];
    bTreeNode *sib = child_p[index + 1];

    child->keys[(child->num_of_keys)] = keys[index]; // key of this node is inserted as the last key of its child at this index

    if(!child->leaf_n) // sibling's first child is inserted as the last child of of the child
    {
       child->child_p[(child->num_of_keys)+1] = sib->child_p[0];
    }

    keys[index] = sib->keys[0]; // first key from the sibling is inserted into the key of this node at this index

    for(int i = 1; i < sib->num_of_keys; ++i) // move all keys in the sibling back one
        sib->keys[i-1] = sib->keys[i];

    if(!sib->leaf_n) // move the sibling's child pointers too if it's not a leaf
    {
        for(int i = 1; i < sib->num_of_keys; ++i)
            sib->child_p[i-1] = sib->child_p[i];
    }

    child->num_of_keys = child->num_of_keys + 1; // increase the child's # of keys
    sib->num_of_keys = sib->num_of_keys - 1; // decrease the sibling's # of keys

    return;
}

void bTreeNode::join(int index)
{
    bTreeNode *child = child_p[index];
    bTreeNode *sib = child_p[index + 1];

    // Take a key from the current node and insert it to the (degree - 1) position of child at this index
    child->keys[degree - 1] = keys[index];

    for(int i = 0; i < sib->num_of_keys; ++i) // copy keys from sibling to it's sibling (child[index+1] => child[index])
        child->keys[i + degree] = sib->keys[i];

    if(!child->leaf_n) // if this is not a leaf, copy child pointers from sibling to it's sibling
    {
        for(int i = 0; i < sib->num_of_keys; ++i)
            child->child_p[i + degree] = sib->child_p[i];
    }

    for(int i = index + 1; i < num_of_keys; ++i) // move all keys after this index back one to fill the gap from giving up the key previously
    {
        keys[i-1] = keys[i];
    }

    for(int i = index + 2; i <= num_of_keys; ++i) // move the child pointes after (index + 1) in the current node back one too
        child_p[i-1] = child_p[i];

    child->num_of_keys += sib->num_of_keys+1; // update key count of current node and child node;
    num_of_keys--;

    delete(sib); // free memory of sibling pointer that has been merged
    return;
}
