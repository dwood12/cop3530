#include <iostream>
#include <limits.h>

using namespace std;
const int infinity = 999999999; // initial large value for non-existant path

void floydWarshall(int** graph, int** parent, int n);
void setWeights(int** graph,int a, int b, int c);
void print_path(int** parent, int i, int j);


int main()
{
    int n, e, q, a, b, c, q1, q2; // initial variables for path
    cin >> n >> e >> q; // initialize num. of nodes, num. of edges, and num. of queries
    int** graph = new int*[n]; // multidimensional array to hold edge weight between node i and j (nxn array)
    int** parent= new int*[n]; // holds the path for each node (to be set by Floyd-Warshall)
    for(int i = 0; i < n; i++)
    {
        graph[i] = new int[n];
        parent[i] = new int[n];
    }

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(i == j)
                {
                    graph[i][j] = 0; // path weight from node to itself is 0
                }
            else
                {
                    graph[i][j] = infinity; // all other path weights initially infinite (don't exist yet)
                }
        }
    }


    for(int i = 0; i < e; i++)
    {
        cin >> a >> b >> c; 
        setWeights(graph,a-1,b-1,c); // sets edge weight of a to b equal to c
    }

	floydWarshall(graph,parent,n); // finds min path between all nodes

    for(int i = 0; i < q; i++)
    {
        cin >> q1 >> q2;
        
        if(graph[q1-1][q2-1] >= 10000) // assumes minimum cost of weights will be less than 10000
        {
            cout << "NO PATH" << "\n";
        }
        else if(q1 == q2) // node path to itself has weight of zero
        {
            cout << "cost = 0" << "\n";
            cout << q1 << "-" << q2 << "\n";
        }
        else
        {
            cout << "cost = " << graph[q1-1][q2-1] << "\n"; // prints minimum path cost
            print_path(parent,q1-1,q2-1); // prints path
            cout << "\n";

        }
    }

    return 0;
}

void floydWarshall(int** graph, int** parent, int n)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if((i == j) || (graph[i][j] >= 10000)) // determines if path is possible by checking if path is from node to itself or very large
            {
                parent[i][j] = -1;
            }
            else
            {
                parent[i][j] = i; // sets first node for path
            }
        }
    }

    for(int k = 0; k < n; k++)
    {
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                int nPath = graph[i][k] + graph[k][j]; // if path from i to k and k to j is shorter than i to j, take that path
                if(nPath < graph[i][j])
                {
                    graph[i][j] = nPath;
                    parent[i][j] = parent[k][j]; // give parent correct node for shortest path
                }
            }
        }
    }

}

void setWeights(int** graph, int a, int b, int c)
{
    graph[a][b] = c; //helper function to set input edge weights
}

void print_path(int** parent, int i, int j)
{
    if(i == j) // base case for when parent recurses to first node to find first node in path 
    {
        cout << i+1;
    }

    else
    {
        print_path(parent,i,parent[i][j]); // recursively calls print_path to print the min path from node i to j
        cout << "-" << j+1; // prints path
    }
}
