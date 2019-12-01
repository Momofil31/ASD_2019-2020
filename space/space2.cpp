#include <fstream>
#include <iostream>
#include <set>
#include <stack>
#include <vector>

#define NIL -1
using namespace std;

struct nodo {
    vector<int> vic;
    int CompConn = 0;
    bool isArtPoint = false;
    bool isVicere = false;
};

int N, M, numVicere;

void articulationPoints(vector<nodo> &grafo);
void APUtil(vector<nodo> &grafo, int u, vector<bool> &visited,
            vector<int> &disc, vector<int> &low, vector<int> &parent);

void posiziona(vector<nodo> &grafo);
void check(int st, vector<nodo> &grafo, vector<bool> &visited);
void stampaGrafo(vector<nodo> &G);
void printArtPoints(vector<nodo> &G);

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    vector<nodo> grafo;
    vector<nodo> grafoNoBridges;
    stack<int> permutazNodiGrafoNoBridges;
    vector<int> vettoreCompConnesse;

    in >> N >> M;
    numVicere = 0;

    grafo.resize(N);
    grafoNoBridges.resize(N);

    // prendo grafo da input
    for (int j = 0; j < M; j++) {
        int from, to;
        in >> from >> to;
        grafo[from].vic.push_back(to);
        grafo[to].vic.push_back(from);
    }

    // stampo grafo
    // stampaGrafo(grafo);

    // computa i punti di articolazione
    articulationPoints(grafo);
    printArtPoints(grafo);
    posiziona(grafo);
    out << numVicere << endl;
    for (int u = 0; u < N; u++) {
        if (grafo[u].isVicere) out << u << " ";
    }
    out << endl;
}

void posiziona(vector<nodo> &grafo) {
    vector<bool> visited(N, false);
    for (int i = 0; i < grafo.size(); i++) {
        if (grafo[i].isArtPoint) visited[i] = true;
    }
    for (int i = 0; i < grafo.size(); i++) {
        if (!visited[i]) check(i, grafo, visited);
    }
}

void check(int st, vector<nodo> &grafo, vector<bool> &visited) {
    stack<int> S;
    set<int> articulation;
    S.push(st);
    int n;
    while (!S.empty()) {
        n = S.top();
        S.pop();
        if (!visited[n]) {
            visited[n] = true;
            for (auto vicino : grafo[n].vic) {
                S.push(vicino);
            }
        } else {
            if (grafo[n].isArtPoint) articulation.insert(n);
        }
    }
    if (articulation.size() <= 1) {
        grafo[st].isVicere = true;
        numVicere++;
    }
}

// The function to do DFS traversal. It uses recursive function APUtil()
void articulationPoints(vector<nodo> &grafo) {
    // Mark all the vertices as not visited
    vector<bool> visited(N, false);
    vector<int> disc(N);
    vector<int> low(N);
    vector<int> parent(N, NIL);

    // Call the recursive helper function to find articulation points
    // in DFS tree rooted with vertex 'i'
    for (int i = 0; i < grafo.size(); i++) {
        if (!visited[i]) {
            APUtil(grafo, i, visited, disc, low, parent);
        }
    }
}

// A recursive function that find articulation points using DFS
// traversal u --> The vertex to be visited next visited[] --> keeps
// tract of visited vertices disc[] --> Stores discovery times of
// visited vertices parent[] --> Stores parent vertices in DFS tree ap[]
// --> Store articulation points
void APUtil(vector<nodo> &grafo, int u, vector<bool> &visited,
            vector<int> &disc, vector<int> &low, vector<int> &parent) {
    // A static variable is used for simplicity, we can avoid use of
    // static variable by passing a pointer.
    static int time = 0;

    // Count of children in DFS Tree
    int children = 0;

    // Mark the current node as visited
    visited[u] = true;

    // Initialize discovery time and low value
    disc[u] = low[u] = ++time;

    // Go through all vertices aadjacent to this
    for (auto v : grafo[u].vic) {
        // If v is not visited yet, then make it a child of u
        // in DFS tree and recur for it
        if (!visited[v]) {
            children++;
            parent[v] = u;
            APUtil(grafo, v, visited, disc, low, parent);

            // Check if the subtree rooted with v has a connection to
            // one of the ancestors of u
            low[u] = min(low[u], low[v]);

            // u is an articulation point in following cases

            // (1) u is root of DFS tree and has two or more chilren.
            if (parent[u] == NIL && children > 1) grafo[u].isArtPoint = true;

            // (2) If u is not root and low value of one of its child is
            // more than discovery value of u.
            if (parent[u] != NIL && low[v] >= disc[u])
                grafo[u].isArtPoint = true;

        }
        // Update low value of u for parent function calls.
        else if (v != parent[u])
            low[u] = min(low[u], disc[v]);
    }
}

// UTILITY

void stampaGrafo(vector<nodo> &G) {
    for (int i = 0; i < G.size(); i++) {
        cout << "Nodo " << i << " ha " << G[i].vic.size() << " vicini" << endl;
        for (int v : G[i].vic) {
            cout << "  " << v << endl;
        }
    }
}

// stampa i punti di articolazione
void printArtPoints(vector<nodo> &G) {
    cout << "These are the articulation points: ";
    for (int i = 0; i < G.size(); i++) {
        if (G[i].isArtPoint) {
            cout << i << " ";
        }
    }
    cout << endl;
}