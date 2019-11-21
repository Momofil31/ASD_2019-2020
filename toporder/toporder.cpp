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
void stampaGrafo(vector<nodo> &);

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    in >> N >> M;

    vector<nodo> grafo(N);
    vector<int> ordinamentoTopologico;
    stack<int> permutazioneGrafo;

    // Prendo grafo da input
    for (int j = 0; j < M; j++) {
        int from, to;
        in >> from >> to;
        grafo[from].vic.push_back(to);
    }

    // Stampo grafo
    cout << "-- STAMPO GRAFO --" << endl;
    stampaGrafo(grafo);

    // Ordino grafo su uno stack. L'ordine di estrazione corrisponde
    // all'ordinamento topologico del grafo
    topSort(grafo, permutazioneGrafo);

    // Salvo l'ordinamento in un vettore
    while (!permutazioneGrafo.empty()) {
        ordinamentoTopologico.push_back(permutazioneGrafo.top());
        permutazioneGrafo.pop();
    }

    // Stampo ordinamento
    cout << "Ordinamento topologico: " << endl;
    for (auto i : ordinamentoTopologico) {
        cout << i << " ";
    }
    cout << endl;

    // Stampo su file output ordinamento topologico
    for (auto i : ordinamentoTopologico) {
        out << i << " ";
    }
    out << endl;

    return 0;
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
    cout << "Push sullo stack del nodo: " << u << endl;
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