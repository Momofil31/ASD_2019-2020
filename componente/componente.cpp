#include <fstream>
#include <iostream>
#include <vector>

#include <stack>
using namespace std;

struct nodo {
    vector<int> vic;
};

int N, M;

void compConnDFS(vector<nodo> &, int, int &, vector<int> &);
vector<int> componentiConnesse(vector<nodo> &, stack<int> &);

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    vector<nodo> grafo;
    stack<int> permutazNodiGrafo;
    vector<int> vettoreCompConnesse;
    int numCompConnesse;

    in >> N >> M;

    grafo.resize(N);

    // prendo grafo da input
    for (int j = 0; j < M; j++) {
        int from, to;
        in >> from >> to;
        grafo[from].vic.push_back(to);
    }

    // Hard-coding permutazione grafo (permutazione banale)
    for (int i = 0; i < N; i++) {
        permutazNodiGrafo.push(i);
    }

    // stampo grafo
    for (int i = 0; i < N; i++) {
        cout << "Nodo " << i << " ha " << grafo[i].vic.size() << " vicini"
             << endl;
        for (int v : grafo[i].vic) {
            cout << "  " << v << endl;
        }
    }

    // calcolo componenti connesse
    vettoreCompConnesse = componentiConnesse(grafo, permutazNodiGrafo);

    /*  // stampo componenti connesse
     for (int i = 0; i < N; i++) {
         cout << vettoreCompConnesse[i] << " ";
     }
     cout << endl; */

    // conto componenti connesse (massimo valore nel vettore)
    numCompConnesse =
        *max_element(vettoreCompConnesse.begin(), vettoreCompConnesse.end());

    // stampo numero componenti connesse
    cout << "Il numero di componenti connesse è: " << numCompConnesse << endl;

    return 0;
}

// Funzioni per il calcolo delle componenti connesse

vector<int> componentiConnesse(vector<nodo> &G, stack<int> &S) {
    vector<int> id(N, 0);  // vettore id che identifica la componente connessa a
                           // cui appartiene il nodo in posizione u
    int conta = 0;
    while (!S.empty()) {
        int u = S.top();
        S.pop();
        if (id[u] == 0) {
            cout << "u = " << u << " e id[u] = " << id[u] << endl;
            conta++;
            compConnDFS(G, conta, u, id);
        }
    }
    return id;
}

void compConnDFS(vector<nodo> &G, int conta, int &u, vector<int> &id) {
    id[u] = conta;
    for (auto v : G[u].vic) {
        cout << "-- v = " << v << " e id[u] = " << id[v] << endl;
        if (id[v] == 0) compConnDFS(G, conta, v, id);
    }
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
}