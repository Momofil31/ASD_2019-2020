//#include <bits/stdc++.h>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct edge {
    int dest;
    int weight;
};

struct nodo {
    vector<edge> adj;
    bool visited = false;
    int distance = INT_MAX;
};

int N, M;

vector<int> minPaths(vector<nodo> &, int);
void leggiGrafo(vector<nodo> &);
void stampaGrafo(vector<nodo> &);

// --- MAIN ---

int main() {
    ofstream out("output.txt");
    vector<nodo> grafo;
    leggiGrafo(grafo);
    // Stampo grafo
    cout << "-- STAMPO GRAFO --" << endl;
    stampaGrafo(grafo);
    vector<int> distanze;
    distanze = minPaths(grafo, 0);
    for (int i = 0; i < distanze.size(); i++) {
        cout << "La minima distanza del nodo " << i
             << " da 0 è: " << distanze[i] << endl;
    }
    return 0;
}

vector<int> minPaths(vector<nodo> &G, int r) {
    vector<int> d(N, INT_MAX);  // vettore delle distanze di ogni nodo
                                // dall'origine, nella soluzione di lase
                                // viene salvato nel nodo
    vector<bool> visited(N, false);
    // #1
    priority_queue<pair<int, int>, vector<pair<int, int>>,
                   greater<pair<int, int>>>
        S;

    S.push(make_pair(0, r));
    d[r] = 0;

    while (!S.empty()) {
        // #2
        auto coppia = S.top();
        S.pop();
        int nodo = coppia.second;
        if (!visited[nodo]) {
            visited[nodo] = true;
            for (auto v : G[nodo].adj) {
                int d2 = d[nodo] + v.weight;

                if (d2 < d[v.dest]) {
                    d[v.dest] = d2;
                    S.push(make_pair(d2, v.dest));
                }
            }
        }
    }
    return d;
}
void leggiGrafo(vector<nodo> &G) {
    ifstream in("input.txt");
    in >> N >> M;
    G.resize(N);
    for (int i = 0; i < M; i++) {
        // GRAFO ORIENTATO
        // f è il nodo, t è il nodo di destinazione, w è il peso
        int f, t, w;
        in >> f >> t >> w;
        edge e;
        e.dest = t;
        e.weight = w;
        G[f].adj.push_back(e);

        /* GRAFO NON ORIENTATO
        // aggiunge un altro edge perché assume che il grafo non sia
        orientato e.dest = f; grafo[t].adj.push_back(e); */
    }
}

// UTILITY

void stampaGrafo(vector<nodo> &G) {
    for (int i = 0; i < G.size(); i++) {
        cout << "Nodo " << i << " ha " << G[i].adj.size() << " vicini" << endl;
        for (auto v : G[i].adj) {
            cout << "  " << v.dest << " peso: " << v.weight << endl;
        }
    }
}