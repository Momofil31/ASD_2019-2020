//#include <bits/stdc++.h>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct edge {
    int dest;
    int weight;
    int inizio;
    int vivo;
    int morto;

    edge(int d, int w, int i, int v, int m)
        : dest(d), weight(w), inizio(i), vivo(v), morto(m){};

    int partenza(int t) {
        if (t < inizio) return inizio;
        int ciclo = vivo + morto;
        int pos = (t - inizio) % ciclo;

        if (vivo - pos >= weight) {
            // riesco a passare subito
            return t;
        } else {
            // aspetto la fine del ciclo (nuovo spegnimento)
            return t - pos + ciclo;
        }
    }
};

struct nodo {
    vector<edge> adj;
    bool visited = false;
    int distance = INT_MAX;
    int pred = -1;
};

int N, M;  //#include <bits/stdc++.h>

int minPath(vector<nodo> &, int);
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
    int minDistanza = minPath(grafo, 0);

    cout << "La distanza minima è: " << minDistanza << endl;
    out << minDistanza << endl;

    // Se minDistanza è -1 non ho soluzione quindi interrompo
    if (minDistanza == -1) {
        return 0;
    }

    // recupero il percorso
    stack<int> stack;
    int c = N - 1;  // parto dall'ultimo nodo del grafo (aka nodo di destinaz.)

    while (c != 0) {
        stack.push(c);  // la prima volta metto il nodo di destinaz. per primo
                        // sullo stack
        c = grafo[c].pred;
    }
    // pusho il nodo di partenza
    stack.push(0);

    // svuoto lo stack estreaendo e stampando
    while (!stack.empty()) {
        out << stack.top() << endl;
        cout << stack.top() << endl;
        stack.pop();
    }

    return 0;
}

int minPath(vector<nodo> &G, int r) {
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
            for (auto e : G[nodo].adj) {
                int d2 = e.partenza(d[nodo]) + e.weight;

                if (d2 < d[e.dest]) {
                    d[e.dest] = d2;  // salvo la distanza
                                     // nel vettore delle distanze

                    G[e.dest].pred = nodo;  // il precedente di
                                            // questo nodo di destinazione è
                                            // il nodo che sto visitando
                    S.push(make_pair(d2, e.dest));
                }
            }
        }
    }
    return d[d.size() - 1];
}
void leggiGrafo(vector<nodo> &G) {
    ifstream in("input.txt");
    in >> N >> M;
    G.resize(N);
    for (int i = 0; i < M; i++) {
        int s, t, w, f, y, n;
        in >> s >> t >> w >> f >> y >> n;
        // se il tempo di attraversamento è maggiore del tempo di laser spento
        // scarto l'arco perchè non sarà mai possibile attraversarlo
        if (y >= w) {
            G[s].adj.push_back(edge(t, w, f, y, n));
            G[t].adj.push_back(edge(s, w, f, y, n));
        }
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