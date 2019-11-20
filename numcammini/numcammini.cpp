#include <bits/stdc++.h>
#include <fstream>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;
struct nodo {
    vector<int> vic;
};

int N, M, S, T;
int numCammini, dimCamminoMinimo;
vector<nodo> grafo;

void findAllMinimunPaths_STACK(int s, int d) {
    // Mark all the vertices as not visited
    bool *visited = new bool[N];

    int path_size = 0;  // Initialize path[] as empty

    // Initialize all vertices as not visited
    for (int i = 0; i < N; i++) visited[i] = false;

    stack<int> S;
    S.push(s);
    while (!S.empty()) {
        int tmp = S.top();
        S.pop();

        if (!visited[tmp]) {
            if (tmp == d) {
                if (path_size < dimCamminoMinimo) {
                    numCammini = 1;
                    dimCamminoMinimo = path_size;
                } else if (path_size == dimCamminoMinimo) {
                    numCammini++;
                }
                path_size = 0;
            } else {
                for (auto i : grafo[tmp].vic) {
                    S.push(i);
                }
                path_size++;
            }
            visited[tmp] == true;
        }
    }
}

// A recursive function to print all paths from 'u' to 'd'.
// visited[] keeps track of vertices in current path.
// path[] stores actual vertices and path_size is current size of the path
void findAllMinimunPathsUtil(int u, int d, bool visited[], int &path_size) {
    // Mark the current node and store it in path[]
    visited[u] = true;
    path_size++;

    // If current vertex is same as destination, then print
    // current path[]
    if (u == d) {
        if (path_size - 1 < dimCamminoMinimo) {
            numCammini = 1;
            dimCamminoMinimo = path_size - 1;
        } else if (path_size - 1 == dimCamminoMinimo) {
            numCammini++;
        }
        /* for (int i = 0; i < path_size; i++) {
            cout << path[i] << " ";
        }
        cout << endl;*/
    } else  // If current vertex is not destination
    {
        if (path_size - 1 <=
            dimCamminoMinimo) {  // se sono su un cammino piu lungo di quello
                                 // minimo non controllo
            // Recur for all the vertices adjacent to current vertex
            for (auto i : grafo[u].vic) {
                if (!visited[i])
                    findAllMinimunPathsUtil(i, d, visited, path_size);
            }
        }
    }

    // Remove current vertex from path[] and mark it as unvisited
    path_size--;
    visited[u] = false;
}

// Prints all paths from 's' to 'd'
void findAllMinimunPaths(int s, int d) {
    // Mark all the vertices as not visited
    bool *visited = new bool[N];

    int path_size = 0;  // Initialize path[] as empty

    // Initialize all vertices as not visited
    for (int i = 0; i < N; i++) visited[i] = false;

    // Call the recursive helper function to print all paths
    findAllMinimunPathsUtil(s, d, visited, path_size);
}

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    in >> N >> M >> S >> T;

    grafo.resize(N);

    dimCamminoMinimo = INT_MAX;
    numCammini = 0;

    for (int j = 0; j < M; j++) {
        int from, to;
        in >> from >> to;
        grafo[from].vic.push_back(to);
    }

    findAllMinimunPaths(S, T);

    /* for (auto i : cammini) {
        // cout << "i.size() = " << i.size() << endl;
        if (i.size() < dimCamminoMinimo) {
            dimCamminoMinimo = i.size();
        }
    }
    for (auto i : cammini) {
        if (i.size() == dimCamminoMinimo) {
            numCammini++;
        }
    } */
    // la distanza e' uguale a dimCamminoMinimo - 1
    out << dimCamminoMinimo << " " << numCammini << endl;

    return 0;
}
