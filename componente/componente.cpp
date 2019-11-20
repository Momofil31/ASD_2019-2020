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

vector<int> componentiFortConnesse(vector<nodo> &);
void compConnDFS(vector<nodo> &, int, int, vector<int> &);
vector<int> componentiConnesse(vector<nodo> &, stack<int> &);
void topSort(vector<nodo> &, stack<int> &);
void topSortDFS(vector<nodo> &, int &, vector<bool> &, stack<int> &);
void stampaGrafo(vector<nodo> &);

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    in >> N >> M;

    vector<nodo> grafo(N);
    vector<int> vettoreCompFortConnesse;
    int dimMaxCompConn;
    int numCompConnesse;

    // Prendo grafo da input
    for (int j = 0; j < M; j++) {
        int from, to;
        in >> from >> to;
        grafo[from].vic.push_back(to);
    }

    // Stampo grafo
    cout << "-- STAMPO GRAFO --" << endl;
    stampaGrafo(grafo);

    // calcolo componenti fortemente connesse
    vettoreCompFortConnesse = componentiFortConnesse(grafo);

    // stampo componenti fortemente connesse
    for (int i = 0; i < N; i++) {
        cout << vettoreCompFortConnesse[i] << " ";
    }
    cout << endl;

    // conto componenti connesse (massimo valore nel vettore)
    numCompConnesse = *max_element(vettoreCompFortConnesse.begin(),
                                   vettoreCompFortConnesse.end());
    cout << "Il numero di componenti connesse è: " << numCompConnesse << endl;

    // Calcolo dimensione della più grande componente fortemente connessa
    vector<int> dimComponenti(numCompConnesse, 0);
    for (auto i : vettoreCompFortConnesse) {
        dimComponenti[i - 1]++;  // i-1 perchè i vettori partono da zero !
    }

    dimMaxCompConn = *max_element(dimComponenti.begin(), dimComponenti.end());

    cout << "La dimensionne della più grande componente fort. conn. è: "
         << dimMaxCompConn << endl;

    out << dimMaxCompConn << endl;

    return 0;
}

// Calcolo delle componenti fortemente connesse
vector<int> componentiFortConnesse(vector<nodo> &grafo) {
    stack<int> permutazNodiGrafo;
    vector<nodo> grafoTrasposto(grafo.size());
    // Ordinamento topologico del grafo
    topSort(grafo, permutazNodiGrafo);

    // Calcolo grafo trasposto
    for (int u = 0; u < N; u++) {
        for (int v : grafo[u].vic) {
            grafoTrasposto[v].vic.push_back(u);
        }
    }

    // Stampo grafo trasposto
    cout << "-- STAMPO GRAFO TRASPOSTO --" << endl;
    stampaGrafo(grafoTrasposto);

    return componentiConnesse(grafoTrasposto, permutazNodiGrafo);
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

void compConnDFS(vector<nodo> &G, int conta, int u, vector<int> &id) {
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