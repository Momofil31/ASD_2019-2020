// C++ program to print all paths from a source to destination.
#include <fstream>
#include <iostream>
#include <list>
#include <vector>

using namespace std;

int counter = 0;

// A directed graph using adjacency list representation
class Graph {
    int V;           // No. of vertices in graph
    list<int> *adj;  // Pointer to an array containing adjacency lists

    // A recursive function used by printAllPaths()
    void printAllPathsUtil(int, int, bool[], int[], int &);

   public:
    Graph(int V);  // Constructor
    void addEdge(int u, int v);

    int countPaths(int s, int d);
    void countPathsUtil(int u, int d, bool visited[], int &pathCount);
};

Graph::Graph(int V) {
    this->V = V;

    adj = new list<int>[V];
}

void Graph::addEdge(int u, int v) {
    adj[u].push_back(v);  // Add v to u’s list.
}
// Returns count of paths from 's' to 'd'
int Graph::countPaths(int s, int d) {
    // Mark all the vertices
    // as not visited
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++) {
        visited[i] = false;
    }

    // Call the recursive helper
    // function to print all paths
    int pathCount = 0;
    countPathsUtil(s, d, visited, pathCount);
    return pathCount;
}

void Graph::countPathsUtil(int u, int d, bool visited[], int &pathCount) {
    visited[u] = true;

    // If current vertex is same as destination,
    // then increment count
    if (u == d) pathCount++;

    // If current vertex is not destination
    else {
        // Recur for all the vertices adjacent to
        // current vertex
        list<int>::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
            if (!visited[*i]) countPathsUtil(*i, d, visited, pathCount);
    }

    visited[u] = false;
}
// Driver program
int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    // Create a graph given in the above diagram

    int N, M, S, D;
    in >> N >> M >> S >> D;

    int nodeA, nodeB;

    Graph g(N);

    for (int i = 0; i < M; i++) {
        in >> nodeA >> nodeB;
        g.addEdge(nodeA, nodeB);
    }

    cout << "Following are all different paths from " << S << " to " << D
         << endl;
    int paths = g.countPaths(S, D);
    cout << paths << endl;
    out << paths << endl;
    return 0;
}