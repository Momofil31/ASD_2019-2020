#include <fstream>
#include <iostream>
#include <vector>

#include <stack>
#define NIL -1
using namespace std;

struct nodo {
    vector<int> vic;
    int CompConn = 0;
    bool isArtPoint = false;
    bool isVicere = false;
};

int N, M;
vector<pair<int, int>> bridges;

void articulationPoints(vector<nodo> &grafo);
void APUtil(vector<nodo> &grafo, int u, vector<bool> &visited,
            vector<int> &disc, vector<int> &low, vector<int> &parent);

void bridge(vector<nodo> &grafo);
void bridgeUtil(vector<nodo> &grafo, int u, vector<bool> &visited,
                vector<int> &disc, vector<int> &low, vector<int> &parent);

void compConnDFS(vector<nodo> &, int, int &);
void componentiConnesse(vector<nodo> &, stack<int> &);
bool exists(vector<pair<int, int>> &coppie, int a, int b);
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

    // stampo i punti di articolazione
    // printArtPoints(grafo);

    // devo trovare le componenti connesse generate da ogni punto di
    // articolazione

    // trovo i ponti, creo un nuovo grafo senza quei ponti
    bridge(grafo);
    /*
    cout << "I ponti sono: " << endl;
    for (auto edge : bridges) {
        cout << edge.first << ", " << edge.second << endl;
    }
    cout << endl;
    */
    for (int u = 0; u < N; u++) {
        for (int v : grafo[u].vic) {
            if (!exists(bridges, u, v)) {
                grafoNoBridges[u].vic.push_back(v);
            }
        }
    }

    // stampaGrafo(grafoNoBridges);

    // trovo componenti connesse del nuovo grafo
    // Hard-coding permutazione grafo (permutazione banale)
    for (int i = 0; i < N; i++) {
        permutazNodiGrafoNoBridges.push(i);
    }
    componentiConnesse(grafoNoBridges, permutazNodiGrafoNoBridges);

    int maxComp = 0;
    for (int i = 0; i < N; i++) {
        // cout << grafoNoBridges[i].CompConn << " ";
        maxComp = grafoNoBridges[i].CompConn > maxComp
                      ? grafoNoBridges[i].CompConn
                      : maxComp;
    }
    // cout << endl;

    // eseguo algoritmo sul quaderno
    vector<vector<int>> nodiDiOgniComponente(maxComp);
    for (int i = 0; i < N; i++) {
        nodiDiOgniComponente[grafoNoBridges[i].CompConn - 1].push_back(i);
    }

    /* for (int i = 0; i < nodiDiOgniComponente.size(); i++) {
        cout << "Componente " << i << " ha nodi: ";
        for (auto el : nodiDiOgniComponente[i]) {
            cout << el << " ";
        }
        cout << endl;
    } */

    int numVicere = 0;
    for (int i = 0; i < nodiDiOgniComponente.size(); i++) {
        int numArtPoint = 0;
        int lastElemNotArtPoint;
        for (auto el : nodiDiOgniComponente[i]) {
            if (grafo[el].isArtPoint)
                numArtPoint++;
            else {
                lastElemNotArtPoint = el;
            }
        }
        if (numArtPoint <= 1) {
            if (grafo[lastElemNotArtPoint].isVicere == false) {
                grafo[lastElemNotArtPoint].isVicere = true;
                numVicere++;
            }
        }
    }
    out << numVicere << endl;
    for (int u = 0; u < N; u++) {
        if (grafo[u].isVicere) {
            out << u << " ";
        }
    }
    out << endl;
}

void bridge(vector<nodo> &grafo) {
    // Mark all the vertices as not visited
    vector<bool> visited(N, false);
    vector<int> disc(N);
    vector<int> low(N);
    vector<int> parent(N, NIL);

    // Call the recursive helper function to find articulation points
    // in DFS tree rooted with vertex 'i'
    for (int i = 0; i < grafo.size(); i++) {
        if (!visited[i]) {
            bridgeUtil(grafo, i, visited, disc, low, parent);
        }
    }
}

// A recursive function that finds and prints bridges using
// DFS traversal
// u --> The vertex to be visited next
// visited[] --> keeps tract of visited vertices
// disc[] --> Stores discovery times of visited vertices
// parent[] --> Stores parent vertices in DFS tree
void bridgeUtil(vector<nodo> &grafo, int u, vector<bool> &visited,
                vector<int> &disc, vector<int> &low, vector<int> &parent) {
    // A static variable is used for simplicity, we can avoid use of static
    // variable by passing a pointer.
    static int time = 0;

    // Mark the current node as visited
    visited[u] = true;

    // Initialize discovery time and low value
    disc[u] = low[u] = ++time;

    // Go through all vertices adjacent to this
    for (auto v : grafo[u].vic) {
        // If v is not visited yet, then recur for it
        if (!visited[v]) {
            parent[v] = u;
            bridgeUtil(grafo, v, visited, disc, low, parent);
            // Check if the subtree rooted with v has a
            // connection to one of the ancestors of u
            low[u] = min(low[u], low[v]);

            // If the lowest vertex reachable from subtree
            // under v is  below u in DFS tree, then u-v
            // is a bridge
            if (low[v] > disc[u]) bridges.push_back(make_pair(u, v));
        }

        // Update low value of u for parent function calls.
        else if (v != parent[u])
            low[u] = min(low[u], disc[v]);
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

// Funzioni per il calcolo delle componenti connesse

void componentiConnesse(vector<nodo> &G, stack<int> &S) {
    int conta = 0;
    while (!S.empty()) {
        int u = S.top();
        S.pop();
        if (G[u].CompConn == 0) {
            // cout << "u = " << u << " e u.CompConn = " << G[u].CompConn <<
            // endl;
            conta++;
            compConnDFS(G, conta, u);
        }
    }
}

void compConnDFS(vector<nodo> &G, int conta, int &u) {
    G[u].CompConn = conta;
    for (auto v : G[u].vic) {
        // cout << "-- v = " << v << " e v.CompConn = " << G[v].CompConn <<
        // endl;
        if (G[v].CompConn == 0) compConnDFS(G, conta, v);
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

// cerca se un coppia esiste in un vector di coppie di interi

bool exists(vector<pair<int, int>> &coppie, int a, int b) {
    for (auto el : coppie) {
        if ((el.first == a && el.second == b) ||
            (el.first == b && el.second == a))
            return true;
    }
    return false;
}