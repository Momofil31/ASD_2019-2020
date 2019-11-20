#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
#include<bits/stdc++.h> 

using namespace std;
struct nodo {
    vector<int> vic;
    bool visited;
};

int N, M;
vector<nodo> grafo;
vector<vector<int> > matDistanze;
queue<int> Q;

void distanza(int partenza) {
    // cout << "partenza = " << partenza << endl;
    Q.push(partenza);
    matDistanze[partenza][partenza] = 0;

    vector<bool> visited(N, false);
    visited[partenza] = true;
    while (!Q.empty()) {
        // prendo l'elemento in testa alla coda e lo rimuovo
        int tmp = Q.front();
        Q.pop();
        // cout << "temp = " << tmp << endl;
        // itero sui suoi vicini
        for (auto i : grafo[tmp].vic) {
            if (!visited[i]) {
                visited[i] = true;
                Q.push(i);

                matDistanze[partenza][i] = matDistanze[partenza][tmp] + 1;
            }
        }
    }
}

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    in >> N >> M;

    grafo.resize(N);
    matDistanze.resize(N);
    for (int i = 0; i < N; i++) {
        matDistanze[i].resize(N);
    }

    for (int j = 0; j < M; j++) {
        int from, to;
        in >> from >> to;
        grafo[from].vic.push_back(to);
        grafo[to].vic.push_back(from);
        grafo[from].visited = false;
    }

    for (int i = 0; i < N; i++) {
        // cout << "Nodo " << i << " ha " << grafo[i].vic.size() << " vicini"<<
        // endl;
        for (int v : grafo[i].vic) {
            // cout << "  " << v << endl;
        }
    }

    // per ogni nodo computa la distanza con ogni altro nodo
    int maxDist = INT_MIN;
    int temp = INT_MIN;

    for (int i = 0; i < N; i++) {
        distanza(i);
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            // cout << matDistanze[i][j] << " ";
            maxDist =
                (matDistanze[i][j] > maxDist) ? matDistanze[i][j] : maxDist;
        }
        // cout << endl;
    }

    // cout << maxDist << endl;
    out << maxDist << endl;
    return 0;
}
