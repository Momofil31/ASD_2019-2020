#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

struct edge {
    int dest;

    edge(int d) : dest(d){};
};

struct nodo {
    vector<edge> adj;
    bool visited = false;
};

int N, M;

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
    return 0;
}

void stampaGrafo(vector<nodo> &G) {
    for (int i = 0; i < G.size(); i++) {
        cout << "Nodo " << i << " ha " << G[i].adj.size() << " vicini" << endl;
        for (auto v : G[i].adj) {
            cout << "  " << v.dest << endl;
        }
    }
}

void leggiGrafo(vector<nodo> &G) {
    ifstream in("input.txt");
    in >> N >> M;
    G.resize(N);
    for (int i = 0; i < M; i++) {
        // GRAFO ORIENTATO
        // f è il nodo, t è il nodo di destinazione
        int f, t;
        in >> f >> t;

        G[f].adj.push_back(edge(t));

        // GRAFO NON ORIENTATO
        // aggiunge un altro edge perché assume che il grafo non sia
        // orientato
        G[t].adj.push_back(edge(f));
    }
}
