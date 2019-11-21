#include <bits/stdc++.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

struct nodo {
    vector<int> vic;
};

int N, M;

void topSort(vector<nodo> &, stack<int> &);
void topSortDFS(vector<nodo> &, int &, vector<bool> &, stack<int> &);
vector<int> longestPathFromNodeToAll(vector<nodo> &, const int &);
int longestPath(vector<nodo> &);

void stampaGrafo(vector<nodo> &);

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    in >> N >> M;

    vector<nodo> grafo(N);

    // Prendo grafo da input
    for (int j = 0; j < M; j++) {
        int from, to;
        in >> from >> to;
        grafo[from].vic.push_back(to);
    }

    // Stampo grafo
    // cout << "-- STAMPO GRAFO --" << endl;
    stampaGrafo(grafo);

    /*
    int maxDist = 0;
    vector<int> distanza;
    for (int i = 0; i < N; i++) {
        distanza = longestPathFromNodeToAll(grafo, i);
        int tempDist = *max_element(distanza.begin(), distanza.end());
        if (tempDist > maxDist) maxDist = tempDist;
    }
    */
    int maxDist = longestPath(grafo);
    // cout << "Il massimo cammino è: " << maxDist << endl;

    out << maxDist << endl;

    return 0;
}

// Calcola il cammino più lungo da un nodo di partenza a ogni altro nodo in un
// vettore di distanze
int longestPath(vector<nodo> &G) {
    stack<int> stackTS;  // stack per ordinamento topologico
    vector<int> ordineTopologico;
    int maxDist = 0;

    // Calcolo un ordinamento topologico del grafo
    topSort(G, stackTS);

    // salvo l'ordinamento topologico in un vettore
    while (!stackTS.empty()) {
        ordineTopologico.push_back(stackTS.top());
        stackTS.pop();
    }

    // Computo sui vertici in ordine topologico
    for (int k = 0; k < N; k++) {
        int startNode =
            k;  // nodo da cui calcolare le distanze in questa iterazione
        vector<int> dist(M, INT_MIN);
        dist[startNode] = 0;

        // calcolo l'array delle distanze per il k-esimo nodo del grafo e ne
        // salvo la più grande
        for (auto i : ordineTopologico) {
            if (dist[i] != INT_MIN) {
                for (auto j : G[i].vic) {
                    if (dist[j] < dist[i] + 1) {
                        dist[j] = dist[i] + 1;
                    }
                }
            }
        }

        // prendo la distanza più grande
        int tempDist = *max_element(dist.begin(), dist.end());
        if (tempDist > maxDist) maxDist = tempDist;
    }

    return maxDist;
}

// Calcola il cammino più lungo da un nodo di partenza a ogni altro nodo in
// un vettore di distanze
vector<int> longestPathFromNodeToAll(vector<nodo> &G, const int &startNode) {
    vector<int> dist(M, INT_MIN);
    dist[startNode] = 0;

    stack<int> stackTS;  // stack per ordinamento topologico

    // Calcolo un ordinamento topologico del grafo
    topSort(G, stackTS);

    // Computo sui vertici in ordine topologico

    while (!stackTS.empty()) {
        int u = stackTS.top();
        stackTS.pop();

        if (dist[u] != INT_MIN) {
            for (auto i : G[u].vic) {
                if (dist[i] < dist[u] + 1) {
                    dist[i] = dist[u] + 1;
                }
            }
        }
    }

    return dist;
}

// Funzioni per il calcolo dell'ordinamento topologico (TopSort)

void topSort(vector<nodo> &G, stack<int> &S) {
    vector<bool> visitato(N, false);
    for (int u = 0; u < N; u++) {
        if (!visitato[u]) {
            if (!visitato[u]) {
                topSortDFS(G, u, visitato, S);
            }
        }
    }
}

void topSortDFS(vector<nodo> &G, int &u, vector<bool> &visitato,
                stack<int> &S) {
    visitato[u] = true;
    for (auto v : G[u].vic) {
        if (!visitato[v]) {
            topSortDFS(G, v, visitato, S);
        }
    }
    S.push(u);
    // cout << "Push sullo stack del nodo: " << u << endl;
}

// UTILITY

void stampaGrafo(vector<nodo> &G) {
    for (int i = 0; i < G.size(); i++) {
        // cout << "Nodo " << i << " ha " << G[i].vic.size() << " vicini" <<
        // endl;
        for (int v : G[i].vic) {
            // cout << "  " << v << endl;
        }
    }
}